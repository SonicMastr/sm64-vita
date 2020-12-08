#ifdef TARGET_VITA_GLES

#include <EGL/egl.h>
#include <pib.h>
#include <psp2/kernel/processmgr.h>

#include "gfx_window_manager_api.h"

#ifdef VERSION_EU
    #define FRAMERATE 25
#else
    #define FRAMERATE 30
#endif

static EGLDisplay display = NULL;
static EGLSurface surface;

static surface_width, surface_height;

static const uint64_t frametime = 1000000 / FRAMERATE;

void gfx_vita_init(const char *game_name, bool start_in_fullscreen) {
    EGLint majorVersion;
    EGLint minorVersion;
    EGLint numConfigs = 0;
    EGLConfig config;
    EGLint configAttribs[] = {
        EGL_RED_SIZE, 8,
        EGL_GREEN_SIZE, 8,
        EGL_BLUE_SIZE, 8,
        EGL_ALPHA_SIZE, 8,
        EGL_DEPTH_SIZE, 32,
        EGL_STENCIL_SIZE, 8,
        EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
        EGL_NONE};
    const EGLint contextAttribs[] = {
        EGL_CONTEXT_CLIENT_VERSION, 2,
        EGL_NONE };

    pibInit(PIB_SHACCCG | PIB_ENABLE_MSAA);
    display = eglGetDisplay(0);

    eglInitialize(display, &majorVersion, &minorVersion);

    eglBindAPI(EGL_OPENGL_ES_API);

    eglChooseConfig(display, configAttribs, &config, 1, &numConfigs);

    surface = eglCreateWindowSurface(display, config, 1, NULL);

    EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, contextAttribs);

    eglMakeCurrent(display, surface, surface, context);
    eglQuerySurface(display, surface, EGL_WIDTH, &surface_width);
    eglQuerySurface(display, surface, EGL_HEIGHT, &surface_height);
}

void gfx_vita_set_keyboard_callbacks(bool (*on_key_down)(int scancode), bool (*on_key_up)(int scancode),
                                     void (*on_all_keys_up)()) {
}

void gfx_vita_set_fullscreen_changed_callback(void (*on_fullscreen_changed)(bool is_now_fullscreen)) {
}

void gfx_vita_set_fullscreen(bool enable) {
}

void gfx_vita_main_loop(void (*run_one_game_iter)()) {
    uint64_t t = 0;
    t = sceKernelGetProcessTimeWide();
    run_one_game_iter();
    t = sceKernelGetProcessTimeWide() - t;
    if (t < frametime)
        sceKernelDelayThreadCB(frametime - t);
}

void gfx_vita_get_dimensions(uint32_t *width, uint32_t *height) {
    *width = surface_width;
    *height = surface_height;
}

void gfx_vita_handle_events() {
}

bool gfx_vita_start_frame() {
    return true;
}

void gfx_vita_swap_buffers_begin() {
    eglSwapBuffers(display, surface);
}

void gfx_vita_swap_buffers_end() {
}

double gfx_vita_get_time() {
    uint64_t time = sceKernelGetProcessTimeWide();

    return (double) time / (1.0 * 1000.0 * 1000.0);
}

struct GfxWindowManagerAPI gfx_vita = {
    gfx_vita_init,
    gfx_vita_set_keyboard_callbacks,
    gfx_vita_set_fullscreen_changed_callback,
    gfx_vita_set_fullscreen,
    gfx_vita_main_loop,
    gfx_vita_get_dimensions,
    gfx_vita_handle_events,
    gfx_vita_start_frame,
    gfx_vita_swap_buffers_begin,
    gfx_vita_swap_buffers_end,
    gfx_vita_get_time
};

#endif