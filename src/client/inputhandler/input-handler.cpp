#include <functional>
#include <map>
#include <vector>
#include <iostream>
#include "raylib.h"

#include "input-handler.hpp"

namespace ummo {
	namespace input {

		InputHandler* InputHandler::GetInstance() {
			static InputHandler* instance = new InputHandler();
			return instance;
		}

		void InputHandler::HandleInput() {
			this->ActionKeypressHandlers();
			this->ActionKeydownHandlers();
			this->ActionMouseScrollHandlers();
			this->ActionMouseMoveHandlers();
			this->ActionMouseClickHandlers();
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

		void InputHandler::RegisterKeydownHandler(std::function<void(std::map<KeyboardKey, bool>)> handler) {
			this->keydownHandlers.push_back(handler);
		}

		std::vector<std::function<void(std::map<KeyboardKey, bool>)>> InputHandler::GetKeydownHandlers() {
			return this->keydownHandlers;
		}

		void InputHandler::ActionKeydownHandlers() {
			std::map<KeyboardKey, bool> keysDown;

			for (int i = 0; i <= 400; i++) {
				if (IsKeyDown(i)) {
					keysDown.insert(std::make_pair((KeyboardKey) i, true));
				}
			}

			for (auto handler : this->GetKeydownHandlers()) {
				handler(keysDown);
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

		Vector2 InputHandler::GetPreviousMousePosition() {
			return this->previousMousePosition;
		}

		void InputHandler::SetPreviousMousePosition(Vector2 mousePosition) {
			this->previousMousePosition = mousePosition;
		}

		void InputHandler::ActionMouseMoveHandlers() {
			Vector2 mousePositionDelta = { 0.0f, 0.0f };
			Vector2 mousePosition = GetMousePosition();
			Vector2 previousMousePosition = this->GetPreviousMousePosition();

			mousePositionDelta.x = mousePosition.x - previousMousePosition.x;
			mousePositionDelta.y = mousePosition.y - previousMousePosition.y;

			this->SetPreviousMousePosition(mousePosition);

			for (auto handler : this->GetMouseMoveHandlers()) {
				handler(mousePositionDelta);
			}
		}

		void InputHandler::RegisterMouseClickHandler(std::function<void(Vector2)> handler) {
			this->mouseClickHandlers.push_back(handler);
		}

		std::vector<std::function<void(Vector2)>> InputHandler::GetMouseClickHandlers() {
			return this->mouseClickHandlers;
		}

		void InputHandler::ActionMouseClickHandlers() {
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				std::cout << "Mouse button pressed!" << std::endl;
				std::vector<std::function<void(Vector2)>> mouseClickHandlers = this->GetMouseClickHandlers();
				Vector2 mousePosition = GetMousePosition();

				for (auto handler : mouseClickHandlers) {
					handler(mousePosition);
				}
			}
			
		}
	}
}