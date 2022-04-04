project(ClientCamera)

add_library(top-camera "top-camera.cpp" "include/top-camera.hpp")
target_sources(top-camera PUBLIC "top-camera.cpp")
target_include_directories(top-camera PUBLIC "include/")

target_link_libraries(top-camera input-handler)
target_link_libraries(top-camera characters)

install(TARGETS top-camera DESTINATION "lib/ummo/client/ui/camera")
install(FILES "include/top-camera.hpp" DESTINATION "include/ummo/client/ui/camera")