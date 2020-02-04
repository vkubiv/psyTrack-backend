
file(GLOB  SOURCES *.cpp)

add_library(user-bundle ${SOURCES})
target_link_libraries(user-bundle auth-bundle)
