project(ClientGame)

add_subdirectory("common")
add_subdirectory("characters")
add_subdirectory("inputhandler")
add_subdirectory("ui/camera")

add_executable(${PROJECT_NAME} "Game.cpp")
target_include_directories(${PROJECT_NAME} PUBLIC ".")

target_link_libraries(${PROJECT_NAME} 
	top-camera
	input-handler
	characters
	player-controls
)

target_include_directories(${PROJECT_NAME} PRIVATE "./../lib/raylib-4.0.0_linux_amd64/include")
target_link_directories(${PROJECT_NAME} PRIVATE "../../lib/raylib-4.0.0_linux_amd64/lib")
target_link_libraries(${PROJECT_NAME} raylib)



include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
include(CPack)