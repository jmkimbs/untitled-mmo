#include "Controls.h"
#include <iostream>

#include "src/client/inputhandler/InputHandler.h"
#include "src/client/ui/camera/TopCamera.h"


namespace ummo {
	namespace client {
		namespace controls {

			void Controller::InitializeCameraControls(ummo::camera::TopCamera camera) {

				ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();
				ih->RegisterKeypressHandler(std::bind(&ummo::camera::TopCamera::KeypressUpdate, camera, std::placeholders::_1));
				ih->RegisterMouseScrollHandler(std::bind(&ummo::camera::TopCamera::MouseScrollUpdate, camera, std::placeholders::_1));
				ih->RegisterMouseMoveHandler(std::bind(&ummo::camera::TopCamera::MouseMoveUpdate, camera, std::placeholders::_1));
			}

		}
	}
}