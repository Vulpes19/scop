# scop

## Overview
Scop is a 3D rendering project written in **C++** using **OpenGL** and **SDL2**.

It provides a basic rendering engine capable of loading and displaying 3D models, applying transformations, handling textures, and rendering custom UI menus (main menu, scene menu, etc.) using both OpenGL and SDL_ttf for text rendering.

This project was built entirely from scratch: no external game engines, to deepen understanding of graphics pipelines, matrix transformations, and rendering architectures.

## Features
- 3D Object Rendering
    - Renders `.obj` models with vertex and index buffers.
    - Supports flat-color rendering.
- Texture Rendering
    - Loads and switches between textures (images under assets/textures) dynamically.
    - Supports toggeling between textured and flat-colored modes.
- Transformations
    - Apply translation, rotation and scaling in real time.
    - Independent transformation matrices ensure consistent transformations.
- Camera Control
    - Free camera movement (WASD)
- Menus
    - Main menu, scene selection, and in-scene UI.
    - Text rendering powered by SDL_ttf, with OpenGL integration.
    - scene selection menu shows models that exist under `assets/models`, loads up to 6 models.

## Key Learnings
Through Scop I gained in-depth experience with:
- The OpenGL rendering pipeline.
- Matrix Math for 3D transformation (translation, scaling and rotation)
- Orthographic vs Perspective projections.
- Shader programming (GLSL vertex and fragment shader)
- Integrating SDL2 and OpenGL for mixed 2D/3D rendering
- Managing resources (textures, shaders, and surfaces)
- State management

## Technologies used
| Category                  | Libraries / Tools |
| ------------------------- | ----------------- |
| **Graphics API**          | OpenGL 3.3 Core   |
| **Window & Input**        | SDL2              |
| **Text Rendering**        | SDL_ttf           |
| **Dependency Management** | vcpkg (Windows)|
| **Build System**          | CMake (Windows) Makefile (macOS)|
| **Language**              | C++               |

## Build instructions
### macOS
1. Clone the repository
   ```
   git clone https://github.com/Vulpes19/scop.git
   ```
2. Install dependencies using `Brew`
   ```
   brew install sdl2 sdl2_image sdl2_ttf 
   ```
3. Build the project
   ```
   make
   ```
4. Run the program
   ```
   ./scop
   ```
5. Modify the textures folder for new textures.
    ```
    assets/textures
    ```
6. Modify the models folder for new models.
    ```
    assets/models
    ```
### Windows
...

## Project Structure
```
scop/
│
├── src/                # Core source files
│   ├── main.cpp
│   ├── Scene.cpp
│   ├── MainMenu.cpp
│   ├── FontLoader.cpp
│   └── ...
│
├── include/            # Header files
│   ├── Matrix.hpp
│   ├── Shader.hpp
│   ├── TextureLoader.hpp
│   └── ...
│
├── assets/
│   ├── models/         # Loaded 3D models
│   ├── textures/       # Loaded Textures
│   └── fonts/
│
├── shaders/            # Vertex & Fragment shaders
│
├── ext/
│   ├── glad            # Load OpenGL using Glad
│
├── CMakeLists.txt
├── Makefile
├── run.sh
└── README.md
```
## Screenshots
![alt text](https://github.com/Vulpes/scop/common/images/42_red.png "42 Logo in Red")

## Author
**Ayman Baioumy**

Computer Graphics Enthusiast | C++ Developer

**Current Position:** DevOps & Cloud Engineer 
