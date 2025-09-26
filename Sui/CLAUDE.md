# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

Sui is a GUI application framework with an integrated visual designer, built using a custom programming language called "Orc" that transpiles to C/C++. The project includes:

- **Sui Framework**: Core GUI framework with widgets, layouts, and rendering
- **SuiDesigner**: Visual editor/designer application for creating GUI interfaces
- **Orc Runtime**: Custom language runtime with garbage collection
- **3D Graphics**: OpenGL-based 3D rendering engine (Sgl)

## Build System

The project uses CMake with Ninja generator:

- **Build directory**: `build/`
- **Main executable**: `build/Sui.exe` (the designer application)
- **Configuration**: CMake project configured for Visual Studio 2022, C++20, C11

### Build Commands

```bash
# Build the project (assuming CMake and Ninja are configured)
cmake --build build

# The main executable will be at build/Sui.exe
```

## Architecture

### Core Components

1. **Orc Language Runtime** (`src/Orc/`, `UrgcDll/`)
   - Custom programming language with C-like syntax
   - Garbage collection system (URGC - "Urgc Reference Counting")
   - Object-oriented features with virtual tables
   - Files with `.orc` extension contain Orc source code
   - Generated `_orc.c` and `_orc.h` files are transpiled C code

2. **Sui GUI Framework** (`src/Sui/`)
   - `Core/`: Basic UI primitives (View, Window, App, Events, etc.)
   - `View/`: UI widgets (Button, TextView, EditText, ScrollArea, etc.)
   - `Layout/`: Layout managers (LinearLayout, GridLayout, etc.)
   - `Dialog/`: Dialog components

3. **SuiDesigner** (`src/SuiDesigner/`)
   - Visual editor for creating GUI interfaces
   - Asset management system
   - Inspector/property panels
   - Scene hierarchy view
   - Serialization system (BiJson)

4. **3D Graphics Engine** (`src/Sgl/`)
   - OpenGL-based 3D rendering
   - Scene management, cameras, lighting
   - Geometry primitives, materials, shaders
   - 3D object support with animation

5. **Supporting Libraries**
   - **Naga/**: Utility functions (string, file, time, math utilities)
   - **nanovg/**: 2D vector graphics rendering
   - **GL/**: OpenGL wrappers and utilities
   - **Json/**: JSON parsing and serialization

### File Patterns

- `.orc` files: Orc language source code
- `_orc.c` and `_orc.h`: Generated C code from Orc transpilation
- `_extern.cpp`: C++ implementations for Orc external functions
- `_win32_extern.cpp`: Windows-specific implementations

### Key Entry Points

- `src/Main.orc` / `src/Main_orc.c`: Basic application entry point
- `src/SuiDesignerMain.orc` / `src/SuiDesignerMain_orc.c`: Designer application entry point
- `src/MainProject.orc` / `src/MainProject_orc.c`: Project-specific main entry

## Development Workflow

### Working with Orc Files

When modifying `.orc` files, the corresponding `_orc.c` and `_orc.h` files are automatically generated during build. Do not manually edit the generated C files.

### External Functions

Orc code can call external C/C++ functions. These are typically implemented in `_extern.cpp` files and declared in the corresponding `.orc` files with `extern` keyword.

### Asset Management

- `asset/`: Contains application assets (images, fonts, etc.)
- Assets are copied to build directory during build process
- The designer includes an asset browser and file watcher system

### Dependencies

- **OpenGL**: Graphics rendering (opengl32, glu32, glew32)
- **Assimp**: 3D model loading
- **miniaudio**: Audio functionality
- **Roboto fonts**: UI typography (included in root)

## Important Notes

- The project is Windows-focused (many `_win32_extern.cpp` files)
- Uses custom garbage collection system - be careful with object lifecycles
- The Orc language has its own syntax similar to C but with additional features
- Generated C code should not be manually edited
- The designer application (SuiDesigner) is the main user-facing application