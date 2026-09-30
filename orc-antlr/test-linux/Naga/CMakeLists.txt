cmake_minimum_required(VERSION 3.25)

project(Naga)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")

# add_compile_options("/utf-8")


add_definitions(-DNAGA_DLL_EXPORT=)

file(GLOB src 
    ./*.cpp
    ./*.c  
    )



ADD_LIBRARY(Naga SHARED ${src})


# set_target_properties(UrgcDll PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# )
