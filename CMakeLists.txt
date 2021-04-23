cmake_minimum_required(VERSION 3.10)
project(untitled)

# 0. reset
# rm -rf  cmake-build-* CmakeFiles CMakeCache.txt && rm -rf *.cmake
# 1. cotire Download
# git clone https://github.com/sakra/cotire.git
# 2. clion cmake set
# -DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cotire/CMake)
include(cotire)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration -I /usr/local/include/ -I ${PROJECT_SOURCE_DIR}/ac-library")
##########################################################################
add_executable(templ_debug templ_debug.cpp)
get_target_property(_prefixHeaderTemplDebug templ_debug COTIRE_CXX_PREFIX_HEADER)
cotire(templ_debug)
##########################################################################

add_executable(main _0_test/main.cpp)
add_executable(templ_release templ_release.cpp)

set_target_properties(main PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")
set_target_properties(templ_release PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")

cotire(main)
cotire(templ_release)

##########################################################################

add_executable(111_c 10_atcoder/ARC/111_c.cpp 10_atcoder/ABC/190_c.cpp)
cotire(111_c)
add_executable(sigma 99_lib/number/sigma.cpp)
add_executable(keyence2021_b 10_atcoder/ARC/keyence2021_b.cpp)
add_executable(prime 99_lib/number/prime.cpp)
add_executable(sparseTable 99_lib/sparseTable.cpp)
add_executable(190_c 10_atcoder/ABC/190_c.cpp)
add_executable(YetAnotherGraphColoring  _0_test/YetAnotherGraphColoring.cpp)