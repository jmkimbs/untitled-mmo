#include <iostream>
#include <map>
#include <math.h>
#include <cmath>
#include "raylib.h"

#include "TopCamera.h"
#include "src/client/inputhandler/InputHandler.h"

namespace ummo {
	namespace camera {


		TopCamera::TopCamera() {
			this->camera = new Camera3D;
			this->camera->position = (Vector3){ 10.0f, 10.0f, 10.0f };
			this->camera->target = (Vector3){ 0.0f, 0.0f, 0.0f };
			this->camera->up = (Vector3){ 0.0f, 1.0f, 0.0f };
			this->camera->fovy = 90.0f;
			this->camera->projection = CAMERA_PERSPECTIVE;

			this->cameraData = new CameraData;
			this->cameraData->targetDistance = 0;
			this->cameraData->angle = { 0 };

			
			this->LookAtTarget();
			this->StopPanning();


			ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();
			ih->RegisterKeypressHandler(std::bind(&ummo::camera::TopCamera::KeypressUpdate, this, std::placeholders::_1));
			ih->RegisterKeydownHandler(std::bind(&ummo::camera::TopCamera::KeydownUpdate, this, std::placeholders::_1));
			ih->RegisterMouseScrollHandler(std::bind(&ummo::camera::TopCamera::MouseScrollUpdate, this, std::placeholders::_1));
			ih->RegisterMouseMoveHandler(std::bind(&ummo::camera::TopCamera::MouseMoveUpdate, this, std::placeholders::_1));
		}
		
		void TopCamera::LookAtTarget() {
			Camera* c = this->GetCamera();
			CameraData* cd = this->GetCameraData();

			Vector3 v1 = c->position;
			Vector3 v2 = c->target;

			float dx = v2.x - v1.x;
			float dy = v2.y - v1.y;
			float dz = v2.z - v1.z;

			cd->targetDistance = sqrtf(dx*dx + dy*dy + dz*dz);   // Distance to target

			// Camera angle calculation
			cd->angle.x = atan2f(dx, dz);                        // Camera angle in plane XZ (0 aligned with Z, move positive CCW)
			cd->angle.y = atan2f(dy, sqrtf(dx*dx + dz*dz));      // Camera angle in plane XY (0 aligned with X, move positive CW)
		}

		TopCamera::~TopCamera() {
			// delete this->camera;
		}

		Camera3D* TopCamera::GetCamera() {
			return this->camera;
		}

		CameraData* TopCamera::GetCameraData() {
			return this->cameraData;
		}

		void TopCamera::ResetToggles() {
			this->StopPanning();
		}

		void TopCamera::PrintPositionDetails() {
		
		}

		void TopCamera::KeypressUpdate(std::map<KeyboardKey, bool> keysPressed) {
			this->isPanning = false;
			for (auto const& [keyPressed, isPressed] : keysPressed) {
				if (isPressed) {
					switch (keyPressed) {
						// case KEY_I:
						// 	this->ZoomIn(1.0f);
						// 	break;
						// case KEY_O:
						// 	this->ZoomOut(1.0f);
						// 	break;
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

		void TopCamera::KeydownUpdate(std::map<KeyboardKey, bool> keysDown) {
			this->StopPanning();

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

		void TopCamera::MouseMoveUpdate(Vector2 movementVector) {

			Camera* c = this->GetCamera();
			CameraData* cd = this->GetCameraData();

			if (this->IsPanning()) {
				// Camera rotation
				cd->angle.x += movementVector.x * -CAMERA_FREE_MOUSE_SENSITIVITY;
				cd->angle.y += movementVector.y * -CAMERA_FREE_MOUSE_SENSITIVITY;

				// Angle clamp
				if (cd->angle.y > CAMERA_FREE_MIN_CLAMP * DEG2RAD) {
					cd->angle.y = CAMERA_FREE_MIN_CLAMP * DEG2RAD;
				} else if (cd->angle.y < CAMERA_FREE_MAX_CLAMP*DEG2RAD) {
					cd->angle.y = CAMERA_FREE_MAX_CLAMP * DEG2RAD;
				}
			}

			// if (this->IsPanning()) {
			// 	c->target.x += ((movementVector.x * CAMERA_FREE_MOUSE_SENSITIVITY) *cosf(cd->angle.x) + (movementVector.y * -CAMERA_FREE_MOUSE_SENSITIVITY) * sinf(cd->angle.x)*sinf(cd->angle.y)) * (cd->targetDistance / CAMERA_FREE_PANNING_DIVIDER);
			// 	c->target.y += ((movementVector.y * CAMERA_FREE_MOUSE_SENSITIVITY) *cosf(cd->angle.y)) * (cd->targetDistance / CAMERA_FREE_PANNING_DIVIDER);
			// 	c->target.z += ((movementVector.x * -CAMERA_FREE_MOUSE_SENSITIVITY) *sinf(cd->angle.x) + (movementVector.y * -CAMERA_FREE_MOUSE_SENSITIVITY) * cosf(cd->angle.x)*sinf(cd->angle.y)) * (cd->targetDistance / CAMERA_FREE_PANNING_DIVIDER);
			// }
		}

		void TopCamera::MouseScrollUpdate(float scrollAmount) {
			if (scrollAmount > 0.0f) {
				ZoomIn(std::abs(scrollAmount));
			}
			else if (scrollAmount < 0.0f) {
				ZoomOut(std::abs(scrollAmount));
			}
		}

		void TopCamera::ZoomIn(float amount) {
			std::cout << "Zooming in" << std::endl;

			CameraData *cd = this->GetCameraData();
			cd->targetDistance -= amount;
			this->ClampZoom();
		}

		void TopCamera::ZoomOut(float amount) {
			std::cout << "Zooming out" << std::endl;

			CameraData *cd = this->GetCameraData();
			cd->targetDistance += amount;
			this->ClampZoom();
		}

		void TopCamera::ClampZoom() {
			CameraData *cd = this->GetCameraData();

			if (cd->targetDistance > CAMERA_FREE_DISTANCE_MAX_CLAMP) {
				cd->targetDistance = CAMERA_FREE_DISTANCE_MAX_CLAMP;
			}

			if (cd->targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) {
				cd->targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
			}
		}

		void TopCamera::LookDown(float amount) {
			Camera* c = this->GetCamera();
			CameraData* cd = this->GetCameraData();
			
			if ((c->position.y > c->target.y) && (cd->targetDistance == CAMERA_FREE_DISTANCE_MAX_CLAMP) && (amount < 0)) {
				std::cout << "Looking down 1" << std::endl;
				c->target.x += amount * (c->target.x - c->position.x) * CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.y += amount*(c->target.y - c->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.z += amount*(c->target.z - c->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
			}
			else if ((c->position.y > c->target.y) && (c->target.y >= 0)) {
				std::cout << "Looking down 2" << std::endl;
                camera->target.x += amount * (c->target.x - c->position.x) * CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                camera->target.y += amount * (c->target.y - c->position.y) * CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                camera->target.z += amount * (c->target.z - c->position.z) * CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
			}
			else if ((c->position.y > c->target.y) && (c->target.y < 0) && (amount > 0)) {
				std::cout << "Looking down 3" << std::endl;
                cd->targetDistance -= (amount * CAMERA_MOUSE_SCROLL_SENSITIVITY);
                if (cd->targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) {
					cd->targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
				}
			}
		}

		void TopCamera::LookUp(float amount) {
			Camera* c = this->GetCamera();
			CameraData* cd = this->GetCameraData();

			if ((c->position.y < camera->target.y) && (cd->targetDistance == CAMERA_FREE_DISTANCE_MAX_CLAMP) && (amount < 0))
            {
				std::cout << "Looking up 1" << std::endl;
                c->target.x += amount*(c->target.x - c->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.y += amount*(c->target.y - c->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.z += amount*(c->target.z - c->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
            }
            else if ((camera->position.y < camera->target.y) && (camera->target.y <= 0))
            {
				std::cout << "Looking up 2" << std::endl;
                c->target.x += amount*(c->target.x - c->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.y += amount*(c->target.y - c->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;
                c->target.z += amount*(c->target.z - c->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd->targetDistance;

                // if (camera->target.y > 0) camera->target.y = 0.001;
            }
            else if ((c->position.y < c->target.y) && (c->target.y > 0) && (amount > 0))
            {
				std::cout << "Looking up 3" << std::endl;
                cd->targetDistance -= (amount*CAMERA_MOUSE_SCROLL_SENSITIVITY);
                if (cd->targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) cd->targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
            }
		}

		void TopCamera::StartPanning() {
			this->isPanning = true;
		}

		void TopCamera::StopPanning() {
			this->isPanning = false;
		}

		bool TopCamera::IsPanning() {
			return this->isPanning;
		}

		void TopCamera::PanLeft() {
			std::cout << "Panning left" << std::endl;
		}
		
		void TopCamera::PanRight() {
			std::cout << "Panning right" << std::endl;
		}

		void TopCamera::Update() {
			Camera* c = this->GetCamera();
			CameraData* cd = this->GetCameraData();

			c->position.x = -sinf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.x;
			c->position.y = -sinf(cd->angle.y) * cd->targetDistance + c->target.y;
			c->position.z = -cosf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.z;

			// std::cout << "Camera position:\n\tx: " << c->position.x << "\n\ty: " << c->position.y << "\n\tz: " << c->position.z << std::endl;
			// std::cout << "Camera angle:\n\tx: " << cd->angle.x << "\n\ty: " << cd->angle.y << std::endl;
		
		}

	}
}