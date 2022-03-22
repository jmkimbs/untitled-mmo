#include "raylib.h"

#include "TopCamera.h"

namespace ummo {
	namespace camera {

		TopCamera::TopCamera() {
			Camera3D camera = { 0 };
			camera.position = (Vector3){ 10.0f, 10.0f, 10.0f };
			camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
			camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
			camera.fovy = 45.0f;
			camera.projection = CAMERA_PERSPECTIVE;

			this->camera = camera;
		}
		
		Camera3D TopCamera::GetCamera() {
			return this->camera;
		}

	}
}