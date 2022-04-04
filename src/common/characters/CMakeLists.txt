project(CommonCharacters)

add_library(characters "character.cpp" "include/character.hpp")
target_sources(characters PUBLIC "character.cpp")
target_include_directories(characters PUBLIC "include/")

add_library(player "player.cpp" "include/player.hpp" "include/character.hpp")
target_sources(player PUBLIC "player.cpp")
target_include_directories(player PUBLIC "include/")

install(TARGETS characters player DESTINATION "lib/ummo/common/characters")
install(FILES "include/character.hpp" "include/player.hpp" DESTINATION "include/ummo/common/characters")