cmake_minimum_required(VERSION 3.0)
project(demo)

add_definitions(-std=c++14)
set(CMAKE_CXX_STANDARD 14)
set(DEMO_SOURCE demo.cpp)
set(CMAKE_TOOLCHAIN_FILE "D:\\pe\\emsdk\\upstream\\emscripten\\cmake\\Modules\\Platform\\Emscripten.cmake")

message(STATUS "WebAssembly build enabled")
message(STATUS "CMAKE_TOOLCHAIN_FILE='${CMAKE_TOOLCHAIN_FILE}'")
if(DEFINED ENV{EMSCRIPTEN})
    message(STATUS "emscripten environment is loaded")
else()
    message(FATAL_ERROR "emscripten environment is NOT loaded")
endif()

add_executable(wasm ${DEMO_SOURCE})
set_target_properties(wasm 
    PROPERTIES SUFFIX ".html"
    LINK_FLAGS "-Os -s USE_WEBGL2=1 -s FULL_ES3=1 -s USE_GLFW=3 -s WASM=1")
# Library linking handled through LINK_FLAGS above