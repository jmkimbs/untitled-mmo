
#include <iostream>
#include <functional>
#include <map>
#include <math.h>
#include <cmath>
#include "raylib.h"

#include "src/client/characters/player/PlayerControls.h"
#include "src/common/characters/player/Player.h"
#include "src/client/inputhandler/InputHandler.h"

namespace ummo {
	namespace client {
		namespace characters {
			
			void PlayerControls::RegisterMovementInputHandlers(ummo::common::characters::Player& player) {
				ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();
				// ih->RegisterKeypressHandler(std::bind(&ummo::camera::TopCamera::KeypressUpdate, player, std::placeholders::_1));
				// ih->RegisterKeydownHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, , std::placeholders::_1, player));
				ih->RegisterKeydownHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, std::placeholders::_1, std::ref(player)));
				// ih->RegisterMouseScrollHandler(std::bind(&ummo::camera::TopCamera::MouseScrollUpdate, player, std::placeholders::_1));
				// ih->RegisterMouseMoveHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, this, std::placeholders::_1));
			}

			void PlayerControls::MovementKeydownHandler(std::map<KeyboardKey, bool> keysDown, ummo::common::characters::Player& player) {	
				for (auto const& [keyDown, isDown] : keysDown) {
					if (isDown) {
						float dx = 0.0f;
						float dy = 0.0f;
						float dz = 0.0f;
						float dxdash = 0.0f;
						float dydash = 0.0f;
						float dzdash = 0.0f;
						float rotation = player.GetRotation() * DEG2RAD;

						switch (keyDown) {
							case KEY_W:
								dz = -0.1f;
								break;
							case KEY_S:
								dz = 0.1f;
								break;
							case KEY_A:
								dx = -0.1f;
								break;
							case KEY_D:
								dx = 0.1f;
								break;
							case KEY_Q:
								player.Rotate(5.0f);
								break;
							case KEY_E:
								player.Rotate(-5.0f);
								break;
						}

						dxdash = dx * cosf(rotation) + dz * sinf(rotation);
						dydash = dy;
						dzdash = -1 * dx * sinf(rotation) + dz * cosf(rotation);

						player.Move((Vector3) { dxdash, dydash, dzdash });
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