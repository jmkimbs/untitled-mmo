#include <functional>
#include <map>
#include <vector>
#include <iostream>
#include "raylib.h"

#include "InputHandler.h"

namespace ummo {
	namespace input {

		InputHandler* InputHandler::GetInstance() {
			static InputHandler* instance = new InputHandler();
			return instance;
		}

		void InputHandler::HandleInput() {
			this->ActionKeypressHandlers();
			this->ActionMouseScrollHandlers();
			this->ActionMouseMoveHandlers();
		}

		void InputHandler::RegisterKeypressHandler(std::function<void(std::map<KeyboardKey, bool>)> handler) {
			this->keypressHandlers.push_back(handler);
		}

		std::vector<std::function<void(std::map<KeyboardKey, bool>)>> InputHandler::GetKeypressHandlers() {
			// TODO: return a copy
			return this->keypressHandlers;
		}

		void InputHandler::ActionKeypressHandlers() {

			std::map<KeyboardKey, bool> keysPressed;

			KeyboardKey keyPressed = (KeyboardKey) GetKeyPressed();
			while (keyPressed != KEY_NULL) {
				keysPressed.insert(std::make_pair(keyPressed, true));
				keyPressed = (KeyboardKey) GetKeyPressed();
			}

			for (auto handler : this->GetKeypressHandlers()) {
				handler(keysPressed);
			}
		}

		void InputHandler::RegisterMouseScrollHandler(std::function<void(float)> handler) {
			this->mouseScrollHandlers.push_back(handler);
		}

		std::vector<std::function<void(float)>> InputHandler::GetMouseScrollHandlers() {
			return this->mouseScrollHandlers;
		}

		void InputHandler::ActionMouseScrollHandlers() {
			float scrollAmount = GetMouseWheelMove();

			for (auto handler : this->GetMouseScrollHandlers()) {
				handler(scrollAmount);
			}
		}

		void InputHandler::RegisterMouseMoveHandler(std::function<void(Vector2)> handler) {
			this->mouseMoveHandlers.push_back(handler);
		}

		std::vector<std::function<void(Vector2)>> InputHandler::GetMouseMoveHandlers() {
			return this->mouseMoveHandlers;
		}

		void InputHandler::ActionMouseMoveHandlers() {
			Vector2 mousePosChange = { 0.0f, 0.0f };
			Vector2 mousePos = GetMousePosition();
			Vector2 prevMousePos = this->prevMousePos;

			mousePosChange.x = mousePos.x - prevMousePos.x;
			mousePosChange.y = mousePos.y - prevMousePos.y;

			prevMousePos = mousePos;

			for (auto handler : this->GetMouseMoveHandlers()) {
				handler(mousePosChange);
			}
		}

	}
}