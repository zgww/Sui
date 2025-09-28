# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

This is a WebAssembly (WASM) project that demonstrates using GLFW 3.2.1 with Emscripten for creating OpenGL applications that run in web browsers. The project structure includes:

- `demo.cpp` - Main demo application showing GLFW/OpenGL ES 3.0 usage with WebAssembly
- `src/glfw-3.2.1/` - Complete GLFW 3.2.1 library source code
- `src/main.c` - Simple "Hello World" C example
- Generated output files (`hi.html`, `hi.js`, `hi.wasm`) - Compiled WebAssembly artifacts

## Build System

The project uses CMake with Emscripten toolchain for WebAssembly compilation:

### Build Commands

```bash
# Configure CMake for WebAssembly build (requires Emscripten environment)
cmake -B build

# Build the project
cmake --build build

# Alternative: Build specific target
cmake --build build --target wasm
```

### Prerequisites

- Emscripten SDK installed and environment loaded (`EMSCRIPTEN` environment variable must be set)
- CMake 3.0 or higher
- The project expects Emscripten toolchain at: `D:\pe\emsdk\upstream\emscripten\cmake\Modules\Platform\Emscripten.cmake`

### Build Configuration

- Target: WebAssembly (`wasm`)
- C++ Standard: C++14
- Output: HTML file with embedded WebAssembly
- WebGL: Uses WebGL 2.0 with OpenGL ES 3.0
- GLFW: Version 3 (USE_GLFW=3)
- Optimization: `-Os` (optimize for size)

## Architecture

### Core Components

1. **GLFW Integration**: Uses GLFW 3.2.1 for cross-platform window/context creation
2. **WebAssembly Target**: Configured for browser execution via Emscripten
3. **OpenGL ES 3.0**: Graphics rendering using WebGL 2.0 backend
4. **Event Handling**: GLFW callbacks for keyboard input and error handling

### Key Features in demo.cpp

- Conditional compilation for WebAssembly vs native targets (`#ifdef __EMSCRIPTEN__`)
- GLFW window creation with OpenGL ES 3.0 context
- Main loop handling: `emscripten_set_main_loop()` for WebAssembly, traditional loop for native
- Basic keyboard input (ESC to close)
- Error handling and cleanup

## Development Notes

- The project builds both WebAssembly and potentially native targets
- GLFW source is included locally rather than as external dependency
- Generated WebAssembly files (`.html`, `.js`, `.wasm`) are build artifacts
- The CMake configuration checks for Emscripten environment before proceeding