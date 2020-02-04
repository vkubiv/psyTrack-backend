# CMakeList.txt : CMake project for phyTracker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)

include(macros.cmake)

include_directories(${PROJECT_SOURCE_DIR})
add_subdirectory(3d-party)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})


add_subdirectory(micro)
add_subdirectory(bundles)



# Add source to this project's executable.
add_executable (phyTracker "phyTracker.cpp" "phyTracker.h")
target_link_libraries(phyTracker pistache micro cpp-jwt)
#target_include_directories(phyTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} )

# additional target to perform clang-format run, requires clang-format

# get all project files
file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)

add_custom_target(
        clangformat
        COMMAND clang-format
        -style=Mozilla
        -i
        ${ALL_SOURCE_FILES}
)