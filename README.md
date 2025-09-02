# UltraBullet

An aim trainer game that utilizes Bezier curves for smooth trajectory training, written in C using SDL2.

## What are Bezier Curves?

Bezier curves are smooth mathematical curves defined by control points. In UltraBullet, these curves create flowing paths that you must follow precisely with your mouse cursor. The game generates random Bezier curves using four control points:
- Two anchor points (start and end)
- Two control points (determine the curve's shape)

This creates challenging, unpredictable paths that improve your mouse precision and aim.

## Prerequisites

### Installing SDL2

**Windows:**
1. Download SDL2 development libraries from [libsdl.org](https://www.libsdl.org/download-2.0.php)
2. Extract to a folder (e.g., `C:\SDL2`)
3. Download SDL2_image from the same site
4. Extract SDL2_image to the same folder

**WSL/Linux:**
```bash
sudo apt update
sudo apt install libsdl2-dev libsdl2-image-dev
```

## Compilation

### Windows (using MinGW or Visual Studio)

**With MinGW:**
```bash
gcc -I"C:\SDL2\include" -L"C:\SDL2\lib" -o UltraBullet.exe UltraBulletInC\main.c UltraBulletInC\Game.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image
```

**With Visual Studio:**
1. Create a new C project
2. Add SDL2 include and library paths to project settings
3. Link against SDL2.lib, SDL2main.lib, and SDL2_image.lib
4. Build the project

### WSL/Linux

```bash
gcc -o UltraBullet UltraBulletInC/main.c UltraBulletInC/Game.c -lSDL2 -lSDL2_image
```

## How to Play

1. Run the executable: `./UltraBullet` (Linux/WSL) or `UltraBullet.exe` (Windows)
2. A window opens with a randomly generated Bezier curve
3. Move your mouse to the starting circle and click to begin following the curve
4. Keep your cursor precisely on the curve path - straying off will reset your progress
5. Complete the curve to generate a new one
6. Practice to improve your mouse precision and aim!

## Controls

- **Mouse Movement**: Follow the curve
- **Left Click**: Start following the curve when hovering over the start circle
- **ESC/Close Window**: Exit the game

## Files

- `main.c` - Main game loop and initialization
- `Game.c` - Core game logic and rendering functions  
- `Game.h` - Header file with function declarations and structs
