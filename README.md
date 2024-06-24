# Learning SDL2

## Table of Contents
- [Hello SDL](./src/demo1/): Get started making games with your first SDL App.
- [Getting an Image on the Screen](./src/demo2/): Show images on the screen with SDL2.
- [Event Driven Programming](./src/demo3/): Handle events with SDL2.
- [Key Presses](./src/demo4/): Handle keys with SDL2.
- [Optimized Surface Loading and Soft Stretching](./src/demo5/): Optimize your loaded surfaces and stretch them with SDL2.
- [Extension Libraries and Loading Other Image Formats](./src/demo6/): Use SDL extension libraries like SDL_image, SDL_ttf, and SDL_mixer to add functionality to SDL.
- [Texture Loading and Rendering](./src/demo7/): Render Hardware Accelerated Textures With SDL2.
- [Geometry Rendering](./src/demo8/): Render hardware accelerated shapes with SDL2.
- [The Viewport](./src/demo9/): Control your SDL rendering area with the viewport.
- [Color Keying](./src/demo10/): Render images with transparent backgrounds using color keying.
- [Clip Rendering and Sprite Sheets](./src/demo11/): Render parts of textures to use sprite sheets.
- [Color Modulation](./src/demo12/): Change your texture's color using color modulation.
- [Alpha Blending](./src/demo13/): Render transparent textures with SDL2.
- [Animated Sprites and VSync](./src/demo14/): Render animations in sync with the monitor refresh rate with SDL2.
- [Rotation and Flipping](./src/demo15/): Rotate and flip your textures in SDL2.
- [True Type Fonts](./src/demo16/): Render text with TTF fonts in SDL2.
- [Mouse Events](./src/demo17/): Handle mouse input with SDL2.

## Build and Run
### Preparation
#### Opt1: Setup on Windows
- Step1: Install [MSYS2](https://www.msys2.org/)
    From winget:
    ```powershell
    winget install MSYS2.MSYS2 -s winget
    ```
    or from official website: [https://www.msys2.org/](https://www.msys2.org/).
- Step2: Config Environment Variable for msys2
    
    Add `C:\msys64\usr\bin` to `PATH` environment variable.
    ```powershell
    $addPath='C:\msys64\usr\bin;';
    $target='User';
    $path = [Environment]::GetEnvironmentVariable('Path', $target);
    if($path -match ";$"){
        $newPath = $path + $addPath;
    } else { 
        $newPath = $path + ';' + $addPath;
    }
    [Environment]::SetEnvironmentVariable('Path', $newPath, $target)
    ```
- Step3: Install c/c++ compile and debug toolchains
    ```powershell
    pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-gdb make
    ```
- Step4: Install SDL2 devlopment library
    ```powershell
    pacman -S mingw-w64-x86_64-SDL2
    ```
- Step5: Config Environment Variable for mingw-w64 and SDL2
    
    Add `C:\msys64\mingw64\bin` to `PATH` environment variable.
#### Opt2: Setup on Linux

### Build
Just go to root directory of this project and run `make` to build all demos.

## Acknowledgements
- [Beginning Game Programming v2.0](https://lazyfoo.net/tutorials/SDL/index.php)
- [MSYS2](https://www.msys2.org/)