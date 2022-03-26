#pragma once

#include "src/client/inputhandler/InputHandler.h"
#include "src/client/ui/camera/TopCamera.h"

namespace ummo {
	namespace client {
		namespace controls {

			class Controller {
				private:
					// void InitializeMovementControls();
					~Controller() = default;
				public:
					Controller() = default;
					static void InitializeCameraControls(ummo::camera::TopCamera);

			};
		}
	}
}