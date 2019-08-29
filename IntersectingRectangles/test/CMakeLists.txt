
cmake_minimum_required (VERSION 3.8)

set (SOURCES "catch.hpp" "IntersectingTest.cpp")
add_executable(IntersectingTest "${SOURCES}")
target_include_directories (IntersectingTest PUBLIC "../source")
target_link_libraries (IntersectingTest IntersectingRectanglesLib)