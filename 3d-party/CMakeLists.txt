
add_library( cpp-jwt STATIC dymmy.cpp )
target_include_directories( cpp-jwt PUBLIC cpp-jwt/include)

add_library( rapidjson STATIC dymmy.cpp )
target_include_directories( rapidjson PUBLIC rapidjson/include)