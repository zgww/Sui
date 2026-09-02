cmake_minimum_required(VERSION 3.25)

project(Fui)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # <--- This is the key fix
# set(C_STANDARD 11)

# set(CMAKE_C_COMPILER "E:\\pf\\vs2026\\VC\\Tools\\Llvm\\x64\\bin\\clang-cl")
# set(CMAKE_CXX_COMPILER "E:\\pf\\vs2026\\VC\\Tools\\Llvm\\x64\\bin\\clang-cl")
# set(CMAKE_LINKER "E:\\pf\\vs2026\\VC\\Tools\\Llvm\\x64\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\bin\\Hostx64\\x64\\link.exe")

include_directories(fui)
include_directories(fui/GL)
# add_compile_options("/utf-8")

add_definitions(
    -D_CRT_SECURE_NO_WARNINGS 
    # -D_DEBUG
    -DNAGA_STATIC
    -DURGC_STATICAPI
    -D_CONSOLE
    -D_AMD64_
    -DUNICODE
)
# add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
# set(FLAGS "-ftime-trace  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-fno-lto  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
set(WARN_FLAGS "-fexceptions -Wno-int-conversion -Wno-unused-command-line-argument -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-O0  -fsanitize=address  -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer")
# set(FLAGS "-O0  -Xclang --dependent-lib=libcmt -Xclang --dependent-lib=oldnames")
# set(FLAGS "-O0  ")

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

# lto 链接时优化
# set(FLAGS " -flto -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -fexceptions ${FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions ${FLAGS} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS} ${WARN_FLAGS}")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto ${FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS} ${WARN_FLAGS}")

file(COPY fui/lib/glew32.dll  DESTINATION .)
file(COPY fui/asset  DESTINATION .)




file(GLOB src 
    fui/*.cpp
    fui/**/*.cpp

    fui/GL/*.c  
    src/GL/*.cpp


    fui/nanovg/*.c  
    fui/nanovg/*.cpp
    )

# add_definitions(-D_CRT=)
# add_definitions(-DURGC_DLLAPI=)



# add_definitions(-D_CRT=)



add_executable(Fui
    ${src}
    # Sgl/Entry.cpp
    # resource.rc
)

# C++20 module interface units
# file(GLOB sgl_modules CONFIGURE_DEPENDS Sgl/*.ixx)
# target_sources(Fui
#   PRIVATE
#   FILE_SET sgl_modules TYPE CXX_MODULES FILES ${sgl_modules}
# )

# Scan regular sources (e.g. Sgl/Entry.cpp) for module imports
# set_target_properties(Fui PROPERTIES CXX_SCAN_FOR_MODULES ON)

# ADD_LIBRARY(UrgcDll SHARED ${UrgcDll_Src})


# target_link_directories(Sui PRIVATE
#                 "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/Llvm/x64/lib/clang/17/lib/windows"
#                 )


# target_link_options(Sui PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)

# ADD_SUBDIRECTORY(assimp)

target_link_directories(Fui PRIVATE 
    lib
    fui/lib
    # "build/assimp/lib"
    )

target_link_libraries(Fui 

    # clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64
    # asan
    # Orc
    # UrgcDll Naga 

# fui.lib

    opengl32
    glu32
    glew32

    gdi32
    user32
    Comdlg32
    Shell32
    Ole32
    # tgfx

    # assimp
    # miniaudio

    # -fsanitize=address
    )

# ADD_LIBRARY(Orc SHARED ${orcSrc})
# ADD_LIBRARY(Orc STATIC ${orcSrc})
# target_link_libraries(Orc UrgcDll Naga)


# set_target_properties(UrgcDll PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
# )

# set_target_properties(Naga PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
#     ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
# )


# add_executable(TestMini 
#     ${TestMiniSrc}
#     # resource.rc 
# )
# target_link_directories(TestMini PRIVATE 
#     lib
#     "build/assimp/lib"
#     )

# target_link_libraries(TestMini 

#     # clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64
#     # asan
#     Orc
#     UrgcDll Naga 

#     opengl32
#     glu32
#     glew32
#     # tgfx

#     assimp
#     miniaudio

#     # -fsanitize=address
#     )