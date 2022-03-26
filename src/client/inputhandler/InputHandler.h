#pragma once

#include <functional>
#include <map>
#include <vector>
#include "raylib.h"


namespace ummo {
	namespace input {

		class InputHandler {
			private:
				std::vector<std::function<void(std::map<KeyboardKey, bool>)>> keypressHandlers;
				std::vector<std::function<void(float)>> mouseScrollHandlers;
				std::vector<std::function<void(Vector2)>> mouseMoveHandlers;

				std::vector<std::function<void(std::map<KeyboardKey, bool>)>> GetKeypressHandlers();
				void ActionKeypressHandlers();

				std::vector<std::function<void(float)>> GetMouseScrollHandlers();
				void ActionMouseScrollHandlers();

				std::vector<std::function<void(Vector2)>> GetMouseMoveHandlers();
				void ActionMouseMoveHandlers();


				Vector2 prevMousePos;
				InputHandler() = default;
				~InputHandler() = default;

			public:
				static InputHandler& GetInstance();
				
				void HandleInput();

				void RegisterKeypressHandler(std::function<void(std::map<KeyboardKey, bool>)>);
				void RegisterMouseScrollHandler(std::function<void(float)>);
				void RegisterMouseMoveHandler(std::function<void(Vector2)>);
		
		};

	}
}