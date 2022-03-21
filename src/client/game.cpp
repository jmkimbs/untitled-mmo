#include <iostream>
#include "raylib.h"

void HandleInput(Camera *camera) {
	int keyPressed = GetKeyPressed();

	while (keyPressed != KEY_NULL) {
		std::cout << "Keycode pressed: " << keyPressed << std::endl;
		switch (keyPressed) {
			case KEY_L:
				SetTargetFPS(60);
				break;
			case KEY_K:
				SetTargetFPS(30);
				break;
			case KEY_P:
				(*camera).fovy += 1.0f;
				break;
			case KEY_W:
				std::cout << "Hopefully adjusting camera pos..." << std::endl;
				(*camera).position = (Vector3){ 100.0f, 100.0f, 100.0f };
				break;
			case KEY_S:
				std::cout << "Hopefully adjusting camera pos..." << std::endl;
				(*camera).position = (Vector3){ 50.0f, 50.0f, 50.0f };
				break;
		
		}
		keyPressed = GetKeyPressed();
	}
}

int main(void)
{
	InitWindow(1280, 720, "Untitled MMO");
	SetTargetFPS(165);

	while (!WindowShouldClose())
	{

		BeginDrawing();
			ClearBackground(RAYWHITE);

			DrawFPS(10, 10);

			DrawText("Wellcome to the beginnings of the Untitled MMO", 400, 340, 20, LIGHTGRAY);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}