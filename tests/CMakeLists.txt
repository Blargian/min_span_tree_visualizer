# Add source to this project's executable.
add_executable (tests "test.cpp" )

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET tests PROPERTY CXX_STANDARD 20)
endif()