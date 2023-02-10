# CMakeList.txt : CMake project for min_span_tree_visualizer, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (min_span_tree_visualizer "main.cpp"   )
set_property(TARGET min_span_tree_visualizer PROPERTY WIN32_EXECUTABLE FALSE)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET min_span_tree_visualizer PROPERTY CXX_STANDARD 20)
endif()


# TODO: Add tests and install targets if needed.
