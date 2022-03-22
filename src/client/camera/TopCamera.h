#pragma once

#include "raylib.h"

namespace ummo {
	namespace camera {

		class TopCamera {
			private:
				int id;
				Camera3D camera;

			public:
				TopCamera();
				Camera3D GetCamera();
				void ZoomIn();
				void ZoomOut();
				void PanLeft();
				void PanRight();
				void EnableCamera();
				void DisableCamera();

				~TopCamera();
		};

	}
}