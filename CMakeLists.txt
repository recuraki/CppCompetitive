cmake_minimum_required(VERSION 3.10)
project(untitled)

# 0. reset
# rm -rf  cmake-build-* CmakeFiles CMakeCache.txt && rm -rf *.cmake
# 1. cotire Download
# git clone https://github.com/sakra/cotire.git
# 2. clion cmake set
# -DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1

# おまじない
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cotire/CMake)
include(cotire)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration -I /usr/local/include/ -I ${PROJECT_SOURCE_DIR}/ac-library")
##########################################################################
add_executable(templ_debug templ_debug.cpp)
get_target_property(_prefixHeaderTemplDebug templ_debug COTIRE_CXX_PREFIX_HEADER)
##########################################################################

add_executable(main _0_test/main.cpp)
add_executable(main2 _0_test/main.c)
add_executable(templ_release templ_release.cpp)

set_target_properties(main PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")
set_target_properties(templ_release PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")
cotire(main)
cotire(templ_release)
cotire(templ_debug)

##########################################################################
add_executable(field2D 99_lib/field2D/field2D.cpp)