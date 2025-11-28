cmake_minimum_required(VERSION 3.22)

project(Sui)


# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 11)
# set(C_STANDARD 11)

# set(CMAKE_C_COMPILER "clang")
# set(CMAKE_CXX_COMPILER "clang++")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\Llvm\\x64\\bin\\lld-link.exe")
# set(CMAKE_LINKER "C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Tools\\MSVC\\14.35.32215\\bin\\Hostx64\\x64\\link.exe")

include_directories(lib)
include_directories(src)
include_directories(./)
include_directories(UrgcDll)
# add_compile_options("/utf-8")

add_definitions(-D_CRT_SECURE_NO_WARNINGS )
add_definitions(-D_ITERATOR_DEBUG_LEVEL=0)
# set(FLAGS "-ftime-trace  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-fno-lto  -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
set(WARN_FLAGS "-Wno-int-conversion -Wno-unused-command-line-argument -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(FLAGS "-O0  -fsanitize=address  -fsanitize-recover=address -fno-stack-protector -fno-omit-frame-pointer")
# set(FLAGS "-O0  -Xclang --dependent-lib=libcmt -Xclang --dependent-lib=oldnames")
set(FLAGS "-O0 -std=c11 ")

# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded")

# lto 链接时优化
# set(FLAGS " -flto -Wno-int-conversion -Wno-microsoft-enum-forward-reference  -Wno-compare-distinct-pointer-types -Wno-ignored-attributes -Wno-unsequenced -Wno-incompatible-pointer-types")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -flto -fexceptions ${FLAGS}")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexceptions ${FLAGS} ${WARN_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${FLAGS} ${WARN_FLAGS}")
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -flto ${FLAGS}")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${FLAGS} ${WARN_FLAGS}")

#file(COPY lib/glew32.dll  DESTINATION .)
#file(COPY asset  DESTINATION .)





file(GLOB src 
    src/*.cpp
    src/Main_orc.c
    # src/*.c  

    src/Json/*.c  
    src/Json/*.cpp
    )

# add_definitions(-D_CRT=)
# add_definitions(-DURGC_DLLAPI=)

file(GLOB orcSrc 
    ./src/Orc/*.cpp
    ./src/Orc/*.c  
    )


add_executable(Sui 
    ${src}
    # resource.rc 
)


add_subdirectory(UrgcDll)
add_subdirectory(Naga)

# ADD_LIBRARY(UrgcDll SHARED ${UrgcDll_Src})


# target_link_directories(Sui PRIVATE
#                 "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/Llvm/x64/lib/clang/17/lib/windows"
#                 )


# target_link_options(Sui PRIVATE /wholearchive:clang_rt.asan_dynamic_runtime_thunk-x86_64.lib)

# ADD_SUBDIRECTORY(assimp)

target_link_directories(Sui PRIVATE 
    lib
    )

target_link_libraries(Sui 

    # clang_rt.asan_dynamic-x86_64 clang_rt.asan_dynamic_runtime_thunk-x86_64
    # asan
    UrgcDll 
    Orc
    Naga 

    # -fsanitize=address
    )

# ADD_LIBRARY(Orc SHARED ${orcSrc})
ADD_LIBRARY(Orc STATIC ${orcSrc})
target_link_libraries(Orc UrgcDll Naga)


set_target_properties(UrgcDll PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)

set_target_properties(Naga PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}"
)
