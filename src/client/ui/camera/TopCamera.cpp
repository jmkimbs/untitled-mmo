#include <iostream>
#include <map>
#include <math.h>
#include "raylib.h"

#include "TopCamera.h"

namespace ummo {
	namespace camera {


		TopCamera::TopCamera() {
			this->camera = new Camera3D;
			this->camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };
			this->camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
			this->camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
			this->camera->fovy = 90.0f;
			this->camera->projection = CAMERA_PERSPECTIVE;
		}
		
		TopCamera::~TopCamera() {
			// delete this->camera;
		}

		Camera3D* TopCamera::GetCamera() {
			return this->camera;
		}

		void TopCamera::PrintPositionDetails() {
		
		}

		void TopCamera::KeypressUpdate(std::map<KeyboardKey, bool> keysPressed) {
			for (auto const& [keyPressed, isPressed] : keysPressed) {
				if (isPressed) {
					switch (keyPressed) {
						case KEY_I:
							this->ZoomIn();
							break;
						case KEY_O:
							this->ZoomOut();
							break;
						case KEY_J:
							this->PanLeft();
							break;
						case KEY_L:
							this->PanRight();
							break;
					}
				}
			}
		}

		void TopCamera::MouseMoveUpdate(Vector2 movementVector) {

		}

		void TopCamera::MouseScrollUpdate(float scrollAmount) {
			if (scrollAmount > 0.0f) {
				ZoomIn();
			}
			else if (scrollAmount < 0.0f) {
				ZoomOut();
			}
		}

		void TopCamera::ZoomIn() {
			std::cout << "Zooming in" << std::endl;
			CameraData *cd = &ummo::camera::CAMERA;
			
			float zoomSpeed = 1.0;
			cd->targetDistance -= zoomSpeed;
			this->ClampZoom();
		}

		void TopCamera::ZoomOut() {
			std::cout << "Zooming out" << std::endl;
			CameraData *cd = &ummo::camera::CAMERA;

			float zoomSpeed = 1.0;
			cd->targetDistance += zoomSpeed;
			this->ClampZoom();
		}

		void TopCamera::ClampZoom() {
			CameraData* cd = &ummo::camera::CAMERA;

			if (cd->targetDistance > CAMERA_FREE_DISTANCE_MAX_CLAMP) {
				cd->targetDistance = CAMERA_FREE_DISTANCE_MAX_CLAMP;
			}

			if (cd->targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) {
				cd->targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
			}
		}

		void TopCamera::PanLeft() {
			std::cout << "Panning left" << std::endl;
		}
		
		void TopCamera::PanRight() {
			std::cout << "Panning right" << std::endl;
		}

		void TopCamera::Update() {
			Camera* c = this->camera;
			CameraData* cd = &ummo::camera::CAMERA;

			c->position.x = -sinf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.x;
			c->position.y = -sinf(cd->angle.y) * cd->targetDistance + c->target.y;
			c->position.z = -cosf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.z;
		}

	}
}