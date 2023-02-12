# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("min_span_tree_visualizer" VERSION 1.0 
									DESCRIPTION "A minimum spanning tree algorithm visualization tool."
									LANGUAGES CXX

)

# Include sub-projects.
add_subdirectory ("src")

# Configuration for Catch2 

add_subdirectory(lib/Catch2)
add_executable(tests ${PROJECT_SOURCE_DIR}/tests/test.cpp )

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain) #import not to use Catch2::Catch2 here but rather Catch2WithMain 

include(CTest)
include(Catch)
catch_discover_tests(tests)

find_package(glfw3 REQUIRED)
find_package(imgui REQUIRED)

add_executable (min_span_tree_visualizer src/main.cpp)
set_property(TARGET min_span_tree_visualizer PROPERTY WIN32_EXECUTABLE FALSE)
target_include_directories(min_span_tree_visualizer 
  PRIVATE 
    "${CMAKE_CURRENT_LIST_DIR}/src"
)

# TODO: Add tests and install targets if needed.

target_link_libraries(
  min_span_tree_visualizer
  PRIVATE
    glfw
    imgui::imgui
)




