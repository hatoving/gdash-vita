<h1 align="center">
<img align="center" src="https://cdn.cloudflare.steamstatic.com/steam/apps/322170/header.jpg" width="45%"><br>
Geometry Dash · PS Vita Port
</h1>

### Jump and fly your way through danger in this rhythm-based action platformer!
#### Prepare for a near impossible challenge in the world of Geometry Dash. Push your skills to the limit as you jump, fly and flip your way through dangerous passages and spiky obstacles.

<p align="center">
  <a href="#about">About</a> •
  <a href="#set-up-for-end-users">Set-Up (For End-Users)</a> •
  <a href="#controls">Controls</a> •
  <a href="#set-up-for-developers">How To Compile</a> •
  <a href="#credits">Credits</a> •
  <a href="#license">License</a>
</p>

# About

Geometry Dash is a side-scrolling music platforming game series developed by RobTop. The game is known for it's challenging levels and legacy, garnering millions of players and a passionate fanbase making user levels to this day.

This repository contains a loader of the *Android release* of Geometry Dash, based on the Android .so Loader by TheFloW. The loader provides a tailored, minimalistic Android-like environment to run the official ARMv7 game executables on the PS Vita.

***This software does not contain the original code, executables, assets, or other not redistributable parts of the game. The authors do not promote or condone piracy in any way. To launch and play the game on their PS Vita device, users must provide their own legally obtained copy of the game in form of an .apk file.***

# Set-Up (for End-Users)

In order to properly install the game, you'll have to follow these steps precisely:

- Install [kubridge](https://github.com/TheOfficialFloW/kubridge/releases/) and [FdFix](https://github.com/TheOfficialFloW/FdFix/releases/) by copying `kubridge.skprx` and `fd_fix.skprx` to your taiHEN plugins folder (usually `ur0:tai`) and adding two entries to your `config.txt` under `*KERNEL`:
  
```
  *KERNEL
  ur0:tai/kubridge.skprx
  ur0:tai/fd_fix.skprx
```

**Note**: don't install fd_fix.skprx if you're using rePatch plugin!

- Make sure you have `libshacccg.suprx` in the `ur0:/data/` folder on your console. If you don't, follow [this guide](https://samilops2.gitbook.io/vita-troubleshooting-guide/shader-compiler/extract-libshacccg.suprx) to extract it.
- Also make sure that you have `libfmodstudio.suprx`, `libc.suprx` and `libfios2.suprx` in the same folder. If you don't, follow [this guide](https://gist.github.com/hatoving/99253e1b3efdefeaf0ca66e0c5dc7089) to extract those files.
- <u>Legally</u> obtain your copy of [Geometry Dash](https://play.google.com/store/apps/details?id=com.robtopx.geometryjump&hl=en&gl=US)
for Android in form of an `.apk` file. [You can get all the required files directly from your phone](https://stackoverflow.com/questions/11012976/how-do-i-get-the-apk-of-an-installed-app-without-root-access) or by using any APK extractor you can find on Google Play.
- Open the `.apk` with any zip explorer (like [7-Zip](https://www.7-zip.org/)) and extract every single audio file and folders `sfx` and `songs` from the `.apk` into `ux0:data/gdash/assets`. Example of resulting path: `ux0:data/gdash/assets/songs/10000104.ogg`, `ux0:data/gdash/assets/menuLoop.mp3`.
- Obtain the `.so` file called `libcocos2dcpp.so` from the `.apk` and place it in `ux0:data/gdash/`.
- Place the `.apk` file in `ux0:data/gdash/` and rename as `GeometryDash.apk`.
- Install `gdash.vpk` and put `shader.txt` into ``ux0:data/gdash/`` (from [Releases](https://github.com/hatoving/gdash-vita/releases/latest)).

# Controls

The game uses only button to operate; which means you can entirely play this with the touchscreen.

However, there's gamepad support to emulate some controls:

|             Button             | Action                      |
|:------------------------------:|:---------------------------:|
| ![dpadh]                       | Move Player (The Tower)     |
|            ![cross]            | Jump                        |
|      ![circl]/![start]                  | Back/Pause                  |

[cross]: https://raw.githubusercontent.com/v-atamanenko/sdl2sand/master/img/cross.svg "Cross"
[circl]: https://raw.githubusercontent.com/v-atamanenko/sdl2sand/master/img/circle.svg "Circle"
[dpadh]: https://raw.githubusercontent.com/v-atamanenko/sdl2sand/master/img/dpad-left-right.svg "D-Pad Left/Right"
[start]: https://raw.githubusercontent.com/v-atamanenko/sdl2sand/master/img/dpad-start.svg "Start"

# Set-Up (for Developers)

In order to build the loader, you'll need a [vitasdk](https://github.com/vitasdk) build fully compiled with softfp usage.  
You can find a precompiled version [here](https://github.com/vitasdk/buildscripts/releases).  

Additionally, you'll need vitaGl to be compiled with these flags: ``make HAVE_GLSL_SUPPORT=1 SOFTFP_ABI=1 NO_DEBUG=1 install``.

You also have to install FMOD onto your VitaSDK enviroment. You can do that by installing [fmodpp](https://github.com/Rinnegatamante/fmodpp).

After all these requirements are met, you can compile the loader with the following commands:

```bash
cmake -Bbuild .
cmake --build build
```

Also note that this CMakeLists has two "convenience targets". While developing, I highly recommed using them, like this:
```bash
cmake --build build --target send # Build, upload eboot.bin and run (requires vitacompanion)
cmake --build build --target dump # Fetch latest coredump and parse
```

For more information and build options, read the [CMakeLists.txt](CMakeLists.txt).

## Credits
- [Andy "The FloW" Nguyen](https://github.com/TheOfficialFloW/) for the original .so loader.
- [Rinnegatamante](https://github.com/Rinnegatamante/) and [gl33ntwine](https://github.com/v-atamanenko/) for helping me a ton with the port (+ for vitaGL by Rinnegatamante.)
- [CatoTheYounger97](https://github.com/CatoTheYounger97/), [Dexxtrip](https://www.reddit.com/user/Dexxtrip/) and [withLogic](https://github.com/withLogic/) for testing the game out.

Style of the page has been taken from https://github.com/v-atamanenko/baba-is-you-vita.
