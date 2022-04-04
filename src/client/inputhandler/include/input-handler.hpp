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
				std::vector<std::function<void(std::map<KeyboardKey, bool>)>> keydownHandlers;
				std::vector<std::function<void(float)>> mouseScrollHandlers;
				std::vector<std::function<void(Vector2)>> mouseMoveHandlers;
				std::vector<std::function<void(Vector2)>> mouseClickHandlers;

				std::vector<std::function<void(std::map<KeyboardKey, bool>)>> GetKeypressHandlers();
				void ActionKeypressHandlers();

				std::vector<std::function<void(std::map<KeyboardKey, bool>)>> GetKeydownHandlers();
				void ActionKeydownHandlers();

				std::vector<std::function<void(float)>> GetMouseScrollHandlers();
				void ActionMouseScrollHandlers();

				Vector2 previousMousePosition;
				Vector2 GetPreviousMousePosition();
				void SetPreviousMousePosition(Vector2);
				std::vector<std::function<void(Vector2)>> GetMouseMoveHandlers();
				void ActionMouseMoveHandlers();

				std::vector<std::function<void(Vector2)>> GetMouseClickHandlers();
				void ActionMouseClickHandlers();




				InputHandler() = default;

			public:
				static InputHandler* GetInstance();
				
				void HandleInput();

				void RegisterKeypressHandler(std::function<void(std::map<KeyboardKey, bool>)>);
				void RegisterKeydownHandler(std::function<void(std::map<KeyboardKey, bool>)>);
				void RegisterMouseScrollHandler(std::function<void(float)>);
				void RegisterMouseMoveHandler(std::function<void(Vector2)>);
				void RegisterMouseClickHandler(std::function<void(Vector2)>);
				~InputHandler() = default;
		
		};

	}
}