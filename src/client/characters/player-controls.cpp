
#include <iostream>
#include <functional>
#include <map>
#include <math.h>
#include <cmath>
#include "raylib.h"

#include "player-controls.hpp"
#include "player.hpp"
#include "input-handler.hpp"

namespace ummo {
	namespace client {
		namespace characters {
			
			void PlayerControls::RegisterMovementInputHandlers(ummo::common::characters::Player& player, Camera& camera) {
				ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();
				// ih->RegisterKeypressHandler(std::bind(&ummo::camera::TopCamera::KeypressUpdate, player, std::placeholders::_1));
				// ih->RegisterKeydownHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, , std::placeholders::_1, player));
				ih->RegisterKeydownHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, std::placeholders::_1, std::ref(player)));
				// ih->RegisterMouseScrollHandler(std::bind(&ummo::camera::TopCamera::MouseScrollUpdate, player, std::placeholders::_1));
				// ih->RegisterMouseMoveHandler(std::bind(&ummo::client::characters::PlayerControls::MovementKeydownHandler, this, std::placeholders::_1));
				ih->RegisterMouseClickHandler(std::bind(&ummo::client::characters::PlayerControls::MouseClickHandler, std::placeholders::_1, std::ref(player), std::ref(camera)));
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
								dx = 0.5f;
								break;
							case KEY_S:
								dx = -0.5f;
								break;
							case KEY_A:
								dz = -0.5f;
								break;
							case KEY_D:
								dz = 0.5f;
								break;
							case KEY_Q:
								player.Rotate(5.0f);
								break;
							case KEY_E:
								player.Rotate(-5.0f);
								break;
						}

						if (dx != 0.0f || dy != 0.0f || dz != 0.0f) {
							dxdash = dx * cosf(rotation) + dz * sinf(rotation);
							dydash = dy;
							dzdash = -1 * dx * sinf(rotation) + dz * cosf(rotation);

							Vector3 currentPosition = player.GetPosition();
							Vector3 targetPosition = (Vector3) { currentPosition.x + dxdash, currentPosition.y + dydash, currentPosition.z + dzdash };

							player.MoveTo(targetPosition);
						}
					}
				}
			}

			void PlayerControls::MouseClickHandler(Vector2 location, ummo::common::characters::Player& player, Camera& camera) {
				// Vector2 adjustedPosition = GetScreenToWorld2D(location, camera);
				//DrawRay(GetMouseRay(location, camera), BLUE);
				
				Ray clickRay = GetMouseRay(location, camera);
				RayCollision collision = GetRayCollisionModel(clickRay, player.GetMap());

				if (collision.hit) {
					std::cout << "Collision=> x: " << collision.point.x << "; y: " << collision.point.y << "; z: " << collision.point.z << std::endl;
					// Vector2 target = (Vector2) { collision.point.x, collision.point.z };
					// player.SetPosition(collision.point);
					player.MoveTo(collision.point); 
				}
				// std::cout << "Local position"
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

			void PlayerControls::RegisterInputHandlers (ummo::common::characters::Player& player, Camera& camera) {
				RegisterMovementInputHandlers(player, camera);
				RegisterModalInputHandlers(player);
			}

		};
	}
}