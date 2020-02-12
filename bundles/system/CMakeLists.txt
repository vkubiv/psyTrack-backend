
file(GLOB  SOURCES *.cpp)

add_library(system-bundle ${SOURCES})
target_link_libraries(system-bundle pistache)
