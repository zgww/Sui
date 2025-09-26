# Sui

Sui is a GUI application framework with an integrated visual designer, built using a custom programming language called "Orc" that transpiles to C.

## highlight

OrcLang completely resolves the challenge of automatic memory management in C. Based on the URGC (Unique Reference Garbage Collection) algorithm, OrcLang achieves automatic memory reclamation with minimal overhead, making your C development process as simple and effortless as working with high-level languages like Java or JavaScript. 

So based on OrcLang, we can achieve our goal described below.

## Goal 

- Best Performance (you are writing c, nobody can faster then you)
- Simplest Gui Framework (gc free us)
- Smallest Gui Framework <= 10MB (less dependencies, smaller size。 we are native app)
- Fastest Compile Speed (then C++ 😁. I'm tired of C++'s compilation speed. The incremental compilation time for Project C is typically within 1 second.)

## URGC

The Urgc algorithm is fundamentally different from existing GC algorithms. Developed based on reference counting, it is a garbage collection algorithm capable of handling cyclic references. It constructs a reference tree from complex reference graphs by marking one reference in each relationship as the sole reference. Through this reference tree, we can determine when and how to detect cyclic references, and when to reclaim memory.


## Features

- **Custom Orc Programming Language**: C-like syntax with object-oriented features and automatic garbage collection
- **Visual Designer**: Integrated GUI editor for creating interfaces visually
- **3D Graphics Engine**: OpenGL-based 3D rendering with scene management
- **Cross-platform GUI Framework**: Comprehensive widget library with layouts and dialogs
- **Asset Management**: Built-in asset browser and management system

## Project Structure

- **`orc-antlr/`** - OrcLang transpiler based on ANTLR-4(cpp version)
- **`Sui/`** - Sui Gui framework
- **`Sui/src/Orc/`** - Orc language runtime and garbage collection system
- **`Sui/src/Sui/`** - Core GUI framework (widgets, layouts, dialogs)
- **`Sui/src/SuiDesigner/`** - Visual editor application
- **`Sui/src/Sgl/`** - 3D graphics engine
- **`Sui/src/Naga/`** - Utility libraries (string, file, math, time)
- **`Sui/build/`** - Build output directory


## Build Requirements

- **CMake** (3.15 or higher)
- **Ninja** build system
- **Visual Studio 2022** with C++20 support
- **OpenGL** development libraries

## Building

1. Configure the project:
```bash
cmake -B build -G Ninja
```

2. Build the project:
```bash
cmake --build build
```

3. Run the designer:
```bash
./build/Sui.exe
```

## Architecture

### Orc Language
- Custom programming language with C-like syntax
- Object-oriented features with virtual tables
- Automatic garbage collection (URGC - "unique reference garbage collection")
- Transpiles to C for native performance

### GUI Framework
- **Core**: Basic UI primitives (View, Window, App, Events)
- **Widgets**: Button, TextView, EditText, ScrollArea, etc.
- **Layouts**: LinearLayout, GridLayout, and other layout managers
- **Dialogs**: Modal and non-modal dialog components

### cross-platform
- win32 native
- linux (glfw)
- macos (glfw)
- ios native
- android native
- web (wasm)


### 2D Graphics

- nanovg
- skia

### 3D Graphics
- OpenGL-based rendering engine
- Scene management with cameras and lighting
- Support for 3D models, materials, and shaders
- Animation system

## File Types

- **`.orc`** - Orc language source files
- **`_orc.c`** / **`_orc.h`** - Generated C code (auto-generated, don't edit)
- **`_extern.cpp`** - C++ implementations for Orc external functions
- **`_win32_extern.cpp`** - Windows-specific implementations

## Development

When working with Orc files, the corresponding `_orc.c` and `_orc.h` files are automatically generated during build. External C/C++ functions can be called from Orc code by implementing them in `.cpp` files.

## Dependencies

- OpenGL (opengl32, glu32, glew32)
- glfw (cross-platform window toolkit)
- miniaudio (audio functionality)
- nanovg (2D vector graphics)

- Assimp (3D model loading. [optional]) 


## TODO

- [o] threejs style Math/Matrix/Geometry util 
- [-] dark thme
- [-] build a demo 3d scene
- [-] Unified Inspector
- [-] 2D/3D Scene Editor
- [-] Material Inspector

- [-] Android Support
- [-] iOS support 
- [-] linux glfw support 
- [-] macos glfw support 
- [-] web support 

## License

LGPLv2