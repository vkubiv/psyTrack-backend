# GLOB_RECURSE also simplifies your glob expressions
file (GLOB_RECURSE SOURCES *.cpp)

add_library(modules ${SOURCES})
target_include_directories(modules PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(modules rapidjson)
