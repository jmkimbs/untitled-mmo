project(CommonCharacters)

add_library(characters "character.cpp" "include/character.hpp")
target_sources(characters PUBLIC "character.cpp")
target_include_directories(characters PUBLIC "include/")

add_library(player "player.cpp" "include/player.hpp" "include/character.hpp")
target_sources(player PUBLIC "player.cpp")
target_include_directories(player PUBLIC "include/")

add_library(character-utils "character-utils.cpp" "include/character-utils.hpp")
target_sources(character-utils PUBLIC "character-utils.cpp")
target_include_directories(character-utils PUBLIC "include/")

install(TARGETS characters player character-utils DESTINATION "lib/ummo/common/characters")
install(FILES "include/character.hpp" "include/player.hpp" "include/character-utils.hpp" DESTINATION "include/ummo/common/characters")

