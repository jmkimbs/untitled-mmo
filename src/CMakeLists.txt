cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(MMO VERSION 0.0.1)

add_subdirectory("externals")
# add_subdirectory("common")
add_subdirectory("client")
add_subdirectory("server")

configure_file("MMOConfig.h.in" "MMOConfig.h")

# add_executable(Game "src/client/Game.cpp")