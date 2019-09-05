
cmake_minimum_required (VERSION 3.8)

set (BIN_SOURCES "IntersectingRectangles.cpp" "IntersectingRectangles.h")
set (LIB_SOURCES "json.hpp" "MyRectangle.h" "MyRectangle.cpp" "MyIntersection.h" "MyIntersection.cpp")
add_executable (IntersectingRectangles "${BIN_SOURCES}")
add_library (IntersectingRectanglesLib STATIC "${LIB_SOURCES}")
target_link_libraries (IntersectingRectangles IntersectingRectanglesLib)