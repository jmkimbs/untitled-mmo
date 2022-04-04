project(ClientCharacters)

add_library(player-controls "player-controls.cpp" "include/player-controls.hpp")
target_sources(player-controls PUBLIC "player-controls.cpp")
target_include_directories(player-controls PUBLIC "include/")


# include_directories("${CommonCharacters_SOURCE_DIR}")
target_link_libraries(player-controls player)
target_link_libraries(player-controls input-handler)


install(TARGETS player-controls DESTINATION "lib/ummo/client/characters")
install(FILES "include/player-controls.hpp" DESTINATION "include/ummo/include/characters")
