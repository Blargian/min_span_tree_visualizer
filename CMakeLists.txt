# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.20)

project ("min_span_tree_visualizer" VERSION 1.0 
									DESCRIPTION "A minimum spanning tree algorithm visualization tool."
									LANGUAGES CXX

)
set(CMAKE_CXX_STANDARD 17)
enable_testing() 

# Include sub-projects.
add_subdirectory ("src")
add_subdirectory ("tests")

find_package(Catch2 REQUIRED)
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

include("sourcelist.cmake")
add_executable (min_span_tree_visualizer ${sources} "src/main.cpp")
set_property(TARGET min_span_tree_visualizer PROPERTY WIN32_EXECUTABLE FALSE)
target_include_directories(min_span_tree_visualizer 
  PRIVATE 
    "${CMAKE_CURRENT_LIST_DIR}/src"
)

add_executable(mstv_tests ${sources} ${testsources})
target_link_libraries(mstv_tests PRIVATE Catch2::Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(CTest)
include(Catch)
catch_discover_tests(mstv_tests)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET mstv_tests PROPERTY CXX_STANDARD 20)
endif()

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

target_link_libraries(
  mstv_tests
  PRIVATE
    Catch2::Catch2WithMain
    OpenGL::GL
    glfw
    glad::glad
    imgui::imgui
    implot::implot
	${Boost_LIBRARIES}
)






