
file(GLOB  SOURCES *.cpp)

add_library(auth-bundle ${SOURCES} )
target_include_directories(auth-bundle PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(auth-bundle cpp-jwt)

