#pragma once

#include <map>

#include "raylib.h"

// Camera mouse movement sensitivity
#define CAMERA_MOUSE_MOVE_SENSITIVITY                   0.003f
#define CAMERA_MOUSE_SCROLL_SENSITIVITY                 1.5f

// FREE_CAMERA
#define CAMERA_FREE_MOUSE_SENSITIVITY                   0.01f
#define CAMERA_FREE_DISTANCE_MIN_CLAMP                  1.0f
#define CAMERA_FREE_DISTANCE_MAX_CLAMP                  120.0f
#define CAMERA_FREE_MIN_CLAMP                           85.0f
#define CAMERA_FREE_MAX_CLAMP                          -85.0f
#define CAMERA_FREE_SMOOTH_ZOOM_SENSITIVITY             0.05f
#define CAMERA_FREE_PANNING_DIVIDER                     5.1f

namespace ummo {
	namespace camera {

		typedef struct {

			float targetDistance;
			float playerEyesPosition;
			Vector2 angle;
			Vector2 previousMousePosition;

			int moveControl[6];
			int smoothZoomControl;
			int altControl;
			int panControl;

		} CameraData;

		class TopCamera {
			private:
				int id;
				Camera3D* camera;
				CameraData* cameraData;
				bool isPanning;
				CameraData* GetCameraData();
				void ZoomIn();
				void ZoomOut();
				void ClampZoom();
				void PanLeft();
				void PanRight();
				void SetPos(Camera*, float, float, float);

			public:
				TopCamera();
				Camera3D* GetCamera();
				void KeypressUpdate(std::map<KeyboardKey, bool>);
				void MouseMoveUpdate(Vector2);
				void MouseScrollUpdate(float scrollAmount);

				void Update();
				void PrintPositionDetails();

				~TopCamera();
		};

	}
}