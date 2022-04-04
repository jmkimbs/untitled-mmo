project(ClientInputHandler)

add_library(input-handler "input-handler.cpp" "include/input-handler.hpp")
target_sources(input-handler PUBLIC "input-handler.cpp")
target_include_directories(input-handler PUBLIC "include/")