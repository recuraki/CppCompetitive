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
add_executable(templ_release templ_release.cpp)

#set_target_properties(main PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")
set_target_properties(templ_release PROPERTIES COTIRE_CXX_PREFIX_HEADER_INIT "${_prefixHeaderTemplDebug}")

cotire(main)
cotire(templ_release)
cotire(templ_debug)

##########################################################################

add_executable(sigma 99_lib/number/cumSum1D.cpp)
add_executable(keyence2021_b 10_atcoder/ARC/keyence2021_b.cpp)
add_executable(prime 99_lib/number/prime.cpp)
add_executable(sparseTable 99_lib/sparseTable.cpp)
add_executable(mod 99_lib/number/mod.cpp)
add_executable(binarysearch 99_lib/MinDiffSearch.cpp)
add_executable(medianQueue 99_lib/number/medianQueue.cpp)
add_executable(zigzagMatrix 99_lib/zigzagMatrix.cpp)
add_executable(binSearch 99_lib/binSearch.cpp)
add_executable(zatsu 99_lib/zatsu.cpp)
add_executable(dijkstra 99_lib/graph/dijkstra.cpp)
add_executable(sort 99_lib/sort.cpp)
add_executable(mst 99_lib/graph/mst.cpp)
add_executable(bellmanFord 99_lib/graph/bellmanFord.cpp)
add_executable(scc 98_sample/2sat_yuki274TheWall.cpp)
add_executable(scc_basic 98_sample/scc_basic.cpp)
add_executable(segtree_takoyaki 98_sample/segtree_takoyaki.cpp)
#add_executable(eulerTour 99_lib/graph/eulerTour.cpp)
add_executable(treeSimpleDSF 98_sample/treeSimpleDSF_abc204c.cpp)
add_executable(treeSimpleNodeCount 98_sample/treeSimpleNodeCount.cpp)
add_executable(imos1d 99_lib/imos1d.cpp)
add_executable(LIS 99_lib/LIS.cpp)
add_executable(segtreeTempl 98_sample/segtreeTempl.cpp)
add_executable(rerooting 99_lib/rerooting.cpp)
add_executable(binSearchLib 99_lib/binSearchLib.cpp)