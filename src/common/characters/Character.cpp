#include <iostream>
#include "raylib.h"

#include "Character.h"

namespace ummo {
	namespace common {
		namespace characters {

			Character::Character(int id) {
			}

			Character::~Character() {
				// UnloadModel(this->GetModel());
			}

			void Character::SetModel(Model model) {
				this->model = model;
			}

			Model Character::GetModel() {
				return this->model;
			}
			
			Vector3 Character::GetPosition() {
				return this->position;
			}

			Vector3& Character::GetLivePosition() {
				return this->position;
			}

			float Character::GetRotation() {
				return this->rotation;
			}

			void Character::Move(Vector3 positionDelta) {
				std::cout << "MOVING" << std::endl;
				Vector3 position = this->GetPosition();
				this->SetPosition((Vector3) { position.x + positionDelta.x, position.y + positionDelta.y, position.z + positionDelta.z });
				
				Vector3 newPosition = this->GetPosition();
				std::cout << "New position=> x: " << newPosition.x << "; y: " << newPosition.y << "; z: " << newPosition.z << std::endl;
			
			}

			void Character::SetPosition(Vector3 position) {
				this->position = position;
			}

			void Character::Rotate(float rotationDelta) {
				this->SetRotation(this->GetRotation() + rotationDelta);
			}

			void Character::SetRotation(float rotation) {
				this->rotation = rotation;
			}

		}
	}
}