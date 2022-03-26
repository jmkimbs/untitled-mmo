#include <iostream>
#include <map>
#include <math.h>
#include "raylib.h"

#include "TopCamera.h"

namespace ummo {
	namespace camera {


		TopCamera::TopCamera() {
			Camera3D camera = { 0 };
			camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
			camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
			camera.fovy = 90.0f;
			camera.projection = CAMERA_PERSPECTIVE;

			this->camera = camera;
		}

		Camera3D TopCamera::GetCamera() {
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

			Camera3D* c = &(this->camera);
			CameraData cd = ummo::camera::CAMERA;
			float dx = scrollAmount*(c->target.x - c->position.x)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd.targetDistance;
			c->target.x += dx;
			float dy = scrollAmount*(c->target.y - c->position.y)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd.targetDistance;
			c->target.y += dy;
			float dz = scrollAmount*(c->target.z - c->position.z)*CAMERA_MOUSE_SCROLL_SENSITIVITY/cd.targetDistance;
			c->target.z += dz;

			std::cout << "dx: " << dx << "; dy: " << dy << "; dz: " << dz << "; tarx: " << c->target.x << "; tary: " << c->target.y << "; tarz: " << c->target.z << std::endl;
			// this->ZoomIn(scrollAmount);
		}

		void TopCamera::ZoomIn() {
			std::cout << "Zooming in" << std::endl;
			CameraData *cd = &ummo::camera::CAMERA;
			
			float zoomSpeed = 10.0;
			cd->targetDistance -= zoomSpeed;
			this->ClampZoom();
		}

		void TopCamera::ZoomOut() {
			std::cout << "Zooming out" << std::endl;
			CameraData *cd = &ummo::camera::CAMERA;

			float zoomSpeed = 10.0;
			cd->targetDistance += zoomSpeed;
			this->ClampZoom();
		}

		void TopCamera::ClampZoom() {
			CameraData cd = ummo::camera::CAMERA;

			if (cd.targetDistance > CAMERA_FREE_DISTANCE_MAX_CLAMP) {
				cd.targetDistance = CAMERA_FREE_DISTANCE_MAX_CLAMP;
			}

			if (cd.targetDistance < CAMERA_FREE_DISTANCE_MIN_CLAMP) {
				cd.targetDistance = CAMERA_FREE_DISTANCE_MIN_CLAMP;
			}
		}

		void TopCamera::PanLeft() {
			std::cout << "Panning left" << std::endl;
		}
		
		void TopCamera::PanRight() {
			std::cout << "Panning right" << std::endl;
		}

		void TopCamera::SetPos(Camera *camera, float posx, float posy, float posz) {
			camera->position.x = posx;
			camera->position.y = posy;
			camera->position.z = posz;
		}

		void TopCamera::Update() {
			Camera* c = &(this->camera);
			Vector3* cpos =&(this->camera.position);
			CameraData* cd = &ummo::camera::CAMERA;

			float posx = -sinf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.x;
			c->position.x = -sinf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.x;
			float posy = -sinf(cd->angle.y) * cd->targetDistance + this->camera.target.y;
			c->position.y = -sinf(cd->angle.y) * cd->targetDistance + this->camera.target.y;
			float posz = -cosf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.z;
			c->position.z = -cosf(cd->angle.x) * cd->targetDistance * cosf(cd->angle.y) + c->target.z;

			std::cout << "-------------------------------------------------------------------------" << std::endl;
			std::cout << "posx: " << posx << "; posy: " << posy << "; posz: " << posz << std::endl;
			std::cout << "c pos=> x: " << c->position.x << "; y: " << c->position.y << "; z: " << c->position.y << std::endl;

			//std::cout << "Target distance: " << cd.targetDistance << std::endl;
			std::cout << "camera pos=> x: " << this->camera.position.x << "; y: " << this->camera.position.y << "; z: " << this->camera.position.y << std::endl;

			cpos->x = posx;
			cpos->y = posy;
			cpos->z = posz;
			std::cout << "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++" << std::endl;
			std::cout << "c pos=> x: " << c->position.x << "; y: " << c->position.y << "; z: " << c->position.y << std::endl;

			//std::cout << "Target distance: " << cd.targetDistance << std::endl;
			std::cout << "camera pos=> x: " << this->camera.position.x << "; y: " << this->camera.position.y << "; z: " << this->camera.position.y << std::endl;
			std::cout << "-------------------------------------------------------------------------" << std::endl;
		}

	}
}