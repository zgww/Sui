# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview
This is an ANTLR 4 C++ demo application that implements a parser and Language Server Protocol (LSP) for the "Orc" programming language. The project demonstrates how to build ANTLR runtime as both dynamic and static libraries and use generated parsers.

## Architecture

### Core Components
- **Grammar Definition**: `Orc.g4` - ANTLR grammar file defining the Orc language syntax
- **Generated Parser**: Files in `generated/` directory (OrcLexer.cpp, OrcParser.cpp, visitors, listeners)
- **LSP Implementation**: `OrcLsp.cpp/h` - Language server implementation
- **Symbol Management**: `Symbol.cpp/h`, `SymbolBuilderVisitor.cpp/h` - Symbol table and AST analysis
- **Code Generation**: `GenOrcCodeVisitor.cpp/h` - Translates Orc AST to target code
- **Project Management**: `Project.cpp/h`, `ProjectScanActor.cpp/h` - File system monitoring and project structure

### Key Architectural Patterns
- **Visitor Pattern**: Multiple visitor implementations for different AST traversal purposes (symbol building, type checking, code generation)
- **Actor Model**: `ActorByThread.h`, `LspActor.cpp/h`, `SymbolActor.cpp/h` - Thread-based actor system for concurrent operations
- **LSP Protocol**: Full Language Server Protocol implementation with code completion, diagnostics, and symbol resolution

### Platform Structure
- `Windows/` - Windows-specific build files and main implementation
- `Linux/` - Linux build configuration
- `Mac/` - macOS build configuration
- `generated/` - ANTLR-generated parser/lexer files

## Development Commands

### Grammar Generation
```bash
# Windows
generate-Orc.cmd

# Unix/Linux/macOS
./generate.sh
```
Requires `antlr-4.13.2-complete.jar` in the project root directory.

### Build System
- **Windows**: Use Visual Studio solution `Windows/antlr4cpp-vs2022.sln`
- **Unix/Linux**: Use CMake build system with `CMakeLists.txt`

### CMake Build (Unix/Linux)
```bash
mkdir build && cd build
cmake ..
make
```

## Key Files and Their Purpose

### Core Language Implementation
- `Orc.g4` - Main grammar definition for Orc language
- `OrcParserBase.cpp/h` - Base parser class with custom logic
- `TypeCheckerVisitor.cpp/h` - Semantic analysis and type checking
- `SymbolBuilderVisitor.cpp/h` - Symbol table construction from AST

### LSP and IDE Integration
- `OrcLsp.cpp/h` - Main LSP server implementation
- `CodeCompletion.cpp/h` - Code completion engine
- `CodeCompletionCore.cpp/hpp` - Core completion algorithm

### Utility Libraries
- `FsUtil.cpp/h` - File system utilities
- `StrUtil.cpp/h` - String manipulation utilities
- `JsonUtil.cpp/h` - JSON parsing and generation
- `ThreadUtil.cpp/h` - Threading utilities
- `Utf8Util.cpp/h` - UTF-8 text handling

### Generated Code Output
The `Windows/antlr4-cpp-demo/orc/` directory contains numerous `*_orc.h` files representing generated code structures for different Orc language constructs (classes, functions, control flow, etc.).

## Dependencies
- ANTLR 4.13.2 runtime library
- nlohmann/json (for JSON handling)
- Windows-specific: Win32 APIs
- Cross-platform: Standard C++ libraries

## Notes
- The project uses UTF-8 encoding (`#pragma execution_character_set("utf-8")`)
- Extensive use of ANTLR's visitor pattern for AST traversal
- Multi-threaded architecture using custom actor implementation
- Full LSP implementation suggests this is a production-ready language server