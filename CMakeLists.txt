# CMakeList.txt : CMake project for phyTracker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

add_subdirectory(micro)

# Add source to this project's executable.
add_executable (phyTracker "phyTracker.cpp" "phyTracker.h")
target_link_libraries(phyTracker pistache)

# TODO: Add tests and install targets if needed.
