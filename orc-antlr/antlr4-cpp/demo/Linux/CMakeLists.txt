# orcc 的 Linux/macOS 构建入口
#
# 用法:
#   cmake -S demo/Linux -B build-linux -DCMAKE_BUILD_TYPE=Release
#   cmake --build build-linux -j
#   # 产物: build-linux/orcc
#
# 说明:
# - Windows 主构建入口仍是 demo/Windows/antlr4cpp-vs2022.sln
# - 这里直接把 ANTLR4 C++ runtime 源码一并编进 orcc,
#   不依赖根 CMakeLists(根入口以 WITH_DEMO 方式构建时需要 Java)
# - 需要 GCC 13+ / Clang 16+ (代码使用了 std::format, 即 C++20)

cmake_minimum_required(VERSION 3.15)
project(orcc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

set(REPO_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../..")
set(ORC_DEMO_DIR "${REPO_ROOT}/demo/Windows/antlr4-cpp-demo")
set(GENERATED_DIR "${REPO_ROOT}/demo/generated")
set(RUNTIME_SRC_DIR "${REPO_ROOT}/runtime/src")

# ---------- ANTLR4 runtime 源码 ----------
file(GLOB ANTLR4_RUNTIME_SRC
  "${RUNTIME_SRC_DIR}/*.cpp"
  "${RUNTIME_SRC_DIR}/atn/*.cpp"
  "${RUNTIME_SRC_DIR}/dfa/*.cpp"
  "${RUNTIME_SRC_DIR}/internal/*.cpp"
  "${RUNTIME_SRC_DIR}/misc/*.cpp"
  "${RUNTIME_SRC_DIR}/support/*.cpp"
  "${RUNTIME_SRC_DIR}/tree/*.cpp"
  "${RUNTIME_SRC_DIR}/tree/pattern/*.cpp"
  "${RUNTIME_SRC_DIR}/tree/xpath/*.cpp"
)

# ---------- Orc 语法生成物 ----------
file(GLOB ORC_GENERATED_SRC "${GENERATED_DIR}/Orc*.cpp")

# ---------- orcc 主体源码(与VS工程保持同一份代码) ----------
file(GLOB ORCC_SRC
  "${ORC_DEMO_DIR}/*.cpp"
)
# Win32Utf8Util.cpp 整个文件被 _WIN32 包裹, 非Windows平台直接排除
if(NOT WIN32)
  list(FILTER ORCC_SRC EXCLUDE REGEX "Win32Utf8Util\\.cpp$")
endif()

add_executable(orcc
  ${ANTLR4_RUNTIME_SRC}
  ${ORC_GENERATED_SRC}
  ${ORCC_SRC}
)

target_include_directories(orcc PRIVATE
  "${REPO_ROOT}/runtime/src"
  "${REPO_ROOT}/runtime/src/atn"
  "${REPO_ROOT}/runtime/src/dfa"
  "${REPO_ROOT}/runtime/src/internal"
  "${REPO_ROOT}/runtime/src/misc"
  "${REPO_ROOT}/runtime/src/support"
  "${REPO_ROOT}/runtime/src/tree"
  "${REPO_ROOT}/runtime/src/tree/pattern"
  "${REPO_ROOT}/runtime/src/tree/xpath"
  "${GENERATED_DIR}"
  "${ORC_DEMO_DIR}"
)

find_package(Threads REQUIRED)
target_link_libraries(orcc PRIVATE Threads::Threads)

if(NOT MSVC)
  # 与上游 demo 的GCC构建一致: visitor存在同名重载
  target_compile_options(orcc PRIVATE -Wno-overloaded-virtual -Wno-attributes)
  # 生成的解析器/第三方代码告警较多, 关掉无用的告警保持输出干净
  target_compile_options(orcc PRIVATE -Wno-unused-parameter -Wno-sign-compare -Wno-reorder -Wno-parentheses -Wno-switch)
endif()
