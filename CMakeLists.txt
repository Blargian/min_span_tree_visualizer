# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("min_span_tree_visualizer" VERSION 1.0 
									DESCRIPTION "A minimum spanning tree algorithm visualization tool."
									LANGUAGES CXX

)
set(CMAKE_CXX_STANDARD 17)

# Include sub-projects.
add_subdirectory ("src")

# Configuration for Catch2 

add_subdirectory(lib/Catch2)
add_executable(tests ${PROJECT_SOURCE_DIR}/tests/test.cpp 
"src/graph.h" 
"src/graph.cpp" 
"src/edge.cpp" 
"src/edge.h" 
"src/node.h" 
"src/node.cpp" 
"src/iSubject.h" 
"src/iSubject.cpp"
"src/iObserver.h" 
"src/app.h" 
"src/app_design.h" 
"src/line.h" 
"src/line.cpp" 
"src/app.cpp" 
"src/mst_algo.h" 
"src/prims_algo.cpp" 
"src/prims_algo.h" 
"src/draw.h" 
"src/draw.cpp"
"src/marker.h"
"src/marker.cpp"
"src/snapshot.h" 
"src/snapshot.cpp" 
"src/node_generator_interface.h" 
"src/node_generator_bestcandidate.h" 
"src/node_generator_bestcandidate.cpp" 
"src/edge_generator_interface.h" 
"src/edge_generator_delaunay.h" 
"src/edge_generator_delaunay.cpp"
 "src/triangle.h" 
 "src/triangle.cpp" 
 "src/node_generator_uniform.h" 
 "src/node_generator_uniform.cpp" 
 "src/utility_mstv.h"
 "src/utility_mstv.cpp"
 "src/union_find.h"
 "src/union_find.cpp"
 "src/kruskals_algo.h" 
 "src/kruskals_algo.cpp")

target_link_libraries(
    tests 
    PRIVATE 
     Catch2::Catch2WithMain
     OpenGL::GL
     glfw
     glad::glad
     imgui::imgui
     implot::implot

) #import not to use Catch2::Catch2 here but rather Catch2WithMain 

include(CTest)
include(Catch)
catch_discover_tests(tests)

find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(OpenGL)
find_package(glm CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(implot CONFIG REQUIRED)

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 
find_package(Boost 1.45.0 COMPONENTS Graph) 

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
endif()

add_executable (min_span_tree_visualizer src/main.cpp 
"src/graph.h" 
"src/graph.cpp" 
"src/edge.cpp" 
"src/edge.h"
"src/node.h" 
"src/node.cpp" 
"src/app_design.h" 
"src/app.h" 
"src/iSubject.h" 
"src/iSubject.cpp"
"src/iObserver.h" 
"src/line.h"
"src/line.cpp" 
"src/app.cpp" 
"src/mst_algo.h" 
"src/prims_algo.cpp" 
"src/prims_algo.h" 
"src/draw.h" 
"src/draw.cpp" 
"src/marker.h"
"src/marker.cpp"
"src/snapshot.h" 
"src/snapshot.cpp" 
"src/node_generator_interface.h" 
"src/node_generator_bestcandidate.h" 
"src/node_generator_bestcandidate.cpp" 
"src/edge_generator_interface.h" 
"src/edge_generator_delaunay.h" 
"src/edge_generator_delaunay.cpp"
"src/union_find.h"
"src/union_find.cpp"
 "src/triangle.h" 
 "src/triangle.cpp" 
 "src/node_generator_uniform.h" 
 "src/node_generator_uniform.cpp" 
 "src/utility_mstv.h"
  "src/utility_mstv.cpp"
 "src/kruskals_algo.h" 
 "src/kruskals_algo.cpp")
set_property(TARGET min_span_tree_visualizer PROPERTY WIN32_EXECUTABLE FALSE)
target_include_directories(min_span_tree_visualizer 
  PRIVATE 
    "${CMAKE_CURRENT_LIST_DIR}/src"
)

# TODO: Add tests and install targets if needed.

target_link_libraries(
  min_span_tree_visualizer
  PRIVATE
    OpenGL::GL
    glfw
    glad::glad
    imgui::imgui
    implot::implot
	${Boost_LIBRARIES}
)




