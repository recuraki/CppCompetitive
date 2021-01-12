cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cotire/CMake)
include(cotire)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration -I ${PROJECT_SOURCE_DIR}/ac-library")

add_executable(main _0_test/main.cpp)
#add_executable(prime 99_lib/number/prime.cpp)
#add_executable(_basic _basic.cpp)
add_executable(templ_debug templ_debug.cpp)
#add_executable(string_std 99_lib/string_std.cpp)

cotire(main templ_debug)


# 0. reset
# rm -rf *.cmake cmake-build-* CmakeFiles CMakeCache.txt
# 1. cotire Download
# git clone https://github.com/sakra/cotire.git
# 2. clion cmake set
# -DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1
