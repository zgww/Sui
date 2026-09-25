cmake_minimum_required(VERSION 3.25)

project(UrgcDll)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")

# add_compile_options("/utf-8")


add_definitions(-DURGC_DLL_EXPORT=)

file(GLOB UrgcDll_Src 
    ./*.cpp
    ./*.c  
    )



ADD_LIBRARY(UrgcDll SHARED ${UrgcDll_Src})


# set_target_properties(UrgcDll PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
# )
