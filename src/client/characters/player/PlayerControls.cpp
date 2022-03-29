#include <map>
#include "raylib.h"

#include "src/client/characters/player/PlayerControls.h"
#include "src/common/characters/player/Player.h"

namespace ummo {
	namespace client {
		namespace characters {
			
			void PlayerControls::RegisterMovementInputHandlers(ummo::common::characters::Player& player) {

			}

			void PlayerControls::MovementKeydownHandler(std::map<KeyboardKey, bool> keysDown, ummo::common::characters::Player& player) {
				for (auto const& [keyDown, isDown] : keysDown) {
					if (isDown) {
						switch (keyDown) {
							case KEY_W:
								player.Move((Vector3) {0.0f, 0.0f, 1.0f});
								break;
							case KEY_A:
								player.Move((Vector3) {-1.0f, 0.0f, 0.0f});
								break;
							case KEY_S:
								player.Move((Vector3) { 0.0f, 0.0f, -1.0f });
								break;
							case KEY_D:
								player.Move((Vector3) { 1.0f, 0.0f, 0.0f });
								break;
						}	
					}
				}


				for (auto const& [keyDown, isDown] : keysDown) {
				if (isDown) {
					switch (keyDown) {
						case KEY_I:
							this->ZoomIn(0.25f);
							break;
						case KEY_O:
							this->ZoomOut(0.25f);
							break;
						case KEY_J:
							break;
						case KEY_L:
							break;
						case KEY_LEFT_ALT:
							this->StartPanning();
							break;
					}
				}
			}
			}

			void PlayerControls::RegisterGuildInputHandlers (ummo::common::characters::Player& player) {

			}

			void PlayerControls::RegisterInventoryHandlers (ummo::common::characters::Player& player) {

			}

			void PlayerControls::RegisterSkillManagerHandler (ummo::common::characters::Player& player) {

			}

			void PlayerControls::RegisterModalInputHandlers (ummo::common::characters::Player& player) {
				RegisterGuildInputHandlers(player);
				RegisterInventoryHandlers(player);
				RegisterSkillManagerHandler(player);
			}

			void PlayerControls::RegisterInputHandlers (ummo::common::characters::Player& player) {
				RegisterMovementInputHandlers(player);
				RegisterModalInputHandlers(player);
			}

		};
	}
}