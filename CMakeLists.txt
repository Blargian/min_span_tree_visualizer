# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required(VERSION 3.5)

project ("min_span_tree_visualizer")

# Include sub-projects.
add_subdirectory ("src")

# Configuration for Catch2 

add_subdirectory(lib/Catch2)
add_executable(tests ${PROJECT_SOURCE_DIR}/tests/test.cpp )

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain) #import not to use Catch2::Catch2 here but rather Catch2WithMain 

include(CTest)
include(Catch)
catch_discover_tests(tests)

