# CMakeList.txt : CMake project for phyTracker, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)
set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g")
add_definitions(-DRAPIDJSON_HAS_STDSTRING=1)

include(macros.cmake)

include_directories(${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/bundles)
include_directories(${PROJECT_SOURCE_DIR}/modules)

add_subdirectory(3d-party)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})


add_subdirectory(micro)
add_subdirectory(bundles)
add_subdirectory(modules)


# Add source to this project's executable.
add_executable (phyTracker "phyTracker.cpp" "phyTracker.h")
target_link_libraries(phyTracker OpenSSL::SSL pistache micro cpp-jwt modules auth-bundle system-bundle user-bundle)
target_include_directories(phyTracker PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} PRIVATE ${PROJECT_SOURCE_DIR}/modules PRIVATE ${PROJECT_SOURCE_DIR}/bundles)

file(COPY config DESTINATION config)

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