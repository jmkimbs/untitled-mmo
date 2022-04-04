
project(CommonCharacters)

add_subdirectory("characters")

include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "LICENSE")
set(CPACK_PACKAGE_VERSION_MAJOR "${${PROJECT_NAME}_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${${PROJECT_NAME}_VERSION_MINOR}")
include(CPack)