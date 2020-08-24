cmake_minimum_required(VERSION 3.10)
project(untitled)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cotire/CMake)
include(cotire)

set(CMAKE_CXX_FLAGS "-std=c++17 -O0 -g -Wall -fsanitize=undefined -Wno-deprecated -Wno-unneeded-internal-declaration")
set_source_files_properties(10_atcoder/ABC/abc130/A/main.cpp PROPERTIES COMPILE_FLAGS "-include /usr/include/x86_64-linux-gnu/c++/7/bits/stdc++.h")
set_source_files_properties(99_lib/number/prime.cpp PROPERTIES COMPILE_FLAGS "-include /usr/include/x86_64-linux-gnu/c++/7/bits/stdc++.h")


add_definitions(-DCOTIRE_MINIMUM_NUMBER_OF_TARGET_SOURCES=1)
add_executable(main _0_test/main.cpp)
add_executable(prime 99_lib/number/prime.cpp)

cotire(main prime)


add_executable(_basic _basic.cpp)
