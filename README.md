# Pong_Game

This is a simple Pong Game I have made with plain C++ and SFML. 
The features are:
- 2-player mode (W/S and ↑/↓)
- Collision detection
- Score tracking
- Sound effects
- Font rendering with Poppins

---
## Requirements
- SFML 2.5+
- C++11 or later
- g++ or clang++ (Linux/macOS) or MinGW (Windows)

### On Linux/macOS:

Install SFML:
`sudo apt-get install libsfml-dev`

then compile it with: `g++ -std=c++11 main.cpp -o main -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio`

And then you can run the game with `./main`

### On Windows
Download and install SFML for Windows

Set up SFML in your IDE or with MinGW

Compile using: `g++ -std=c++11 main.cpp -o main.exe -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio`

Or, if you already have the .exe version and .dlls provided, just double-click main.exe.

(Make sure all required .dll files (e.g. sfml-graphics-2.dll, openal32.dll) are in the same folder as main.exe.)

