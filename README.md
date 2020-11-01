# Super Mario 64 Port (Piglet)

- This is a Super Mario 64 PS Vita port using Piglet as the graphics backend over VitaGL. A first look into how the renderer needs barely any modification other than Shaders.
- This repo contains a full decompilation of Super Mario 64 (J), (U), and (E) with minor exceptions in the audio subsystem.
- Naming and documentation of the source code and data structures are in progress.
- Efforts to decompile the Shindou ROM steadily advance toward a matching build.
- Beyond Nintendo 64, it can also target the PS Vita.

This repo does not include all assets necessary for compiling the game.
A prior copy of the game is required to extract the assets.

## Building for the Vita (Piglet)

### Prerequisites
For running this on the PS Vita you will need to install the [Pigs in a Blanket Configuration Tool](https://github.com/SonicMastr/PIB-Configuration-Tool) and install PIB. This also enables custom resolution support up to 1920x1080.

### Build Instructions
1. Install [DolceSDK](https://github.com/DolceSDK/doc)
2. Build and install [Pigs in a Blanket](https://github.com/SonicMastr/Pigs-In-A-Blanket)
3. Clone this Piglet branch, which will create a directory `sm64-vita` and then **enter** it `cd sm64-vita`.
4. Place a Super Mario 64 ROM called `baserom.<VERSION>.z64` into the repository's root directory for asset extraction, where `VERSION` can be `us`, `jp`, or `eu`.
5. Building
    1. Run `make TARGET_VITA_GLES=1 vpk` to build the game. Add `-j4` to improve build time.
6. The installable vpk will be located at `build/us_vita/sm64.<VERSION>.f3dex2e.vpk`

## Known Issues
1. Invincibility Cap visual effect appears as static.

## Contributing

If you want to make it better, fork it and make it better. Thanks. 

## Credits

* WOLFwang for making the livearea assets.
* fgsfds for the initial effort towards porting to the vita.
* The original sm64decomp team for this impressive decompilation.
* The sm64-port team for the work towards porting the decomp to other platforms.
* Bythos for the Audio backend and original Vita port for direction.