#include <iostream>
#include <cmath>
#include "raylib.h"

#include "Character.h"

namespace ummo {
	namespace common {
		namespace characters {

			Character::Character(int id) {
				this->InitializeAttributes(id);
			}

			void Character::InitializeAttributes(int id) {
				this->SetPosition((Vector3) { 0.0f, 0.0f, 0.0f });
				this->MoveTo((Vector3) { 0.0f, 0.0f, 0.0f });
				this->SetRotation(0.0f);
			}

			Character::~Character() {
				UnloadModel(this->GetModel());
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

			Vector3 Character::GetTargetPosition() {
				return this->targetPosition;
			}

			float Character::GetRotation() {
				return this->rotation;
			}

			void Character::Move(Vector3 positionDelta) {
				Vector3 position = this->GetPosition();
				this->SetPosition((Vector3) { position.x + positionDelta.x, position.y + positionDelta.y, position.z + positionDelta.z });	
			}

			void Character::MoveTo(Vector3 position) {
				this->targetPosition = position;
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
			
			void Character::SetMap(Model map) {
				this->map = map;
			}

			Model Character::GetMap() {
				return this->map;
			}

			void Character::Update(float timeDelta) {
				Vector3 currentPosition = this->GetPosition();
				Vector3 targetPosition = this->GetTargetPosition();
				Vector3 direction = { targetPosition.x - currentPosition.x, targetPosition.y - currentPosition.y, targetPosition.z - currentPosition.z };

				float targetDistance = sqrt(pow(direction.x, 2) + pow(direction.y, 2) + pow(direction.z, 2));

				// std::cout << "Current position is=> x: " << currentPosition.x << "; y: " << currentPosition.y << "; z: " << currentPosition.z << std::endl;
				// std::cout << "Target position is=> x: " << targetPosition.x << "; y: " << targetPosition.y << "; z: " << targetPosition.z << std::endl;
				// std::cout << "Direction is=> x: " << direction.x << "; y: " << direction.y << "; z: " << direction.z << std::endl;
				// std::cout << "Target distance is=> " << targetDistance << std::endl;

				if (targetDistance > 0.1f) {
					direction.x = direction.x / targetDistance;
					direction.y = direction.y / targetDistance;
					direction.z = direction.z / targetDistance;
					std::cout << "Normalized direction is=> x: " << direction.x << "; y: " << direction.y << "; z: " << direction.z << std::endl;
				
					direction.x = direction.x * timeDelta * 10;
					direction.y = direction.y * timeDelta * 10;
					direction.z = direction.z * timeDelta * 10;

					this->Move(direction);
					float currentRotation = this->GetRotation();
					float targetRotation = (atan2f(direction.x, direction.z) * RAD2DEG) - 90;
					this->SetRotation(targetRotation);
					std::cout << "Current rotation is=> " << currentRotation << std::endl;
					std::cout << "New rotation is=> " << targetRotation << std::endl;
				}
			}

		}
	}
}