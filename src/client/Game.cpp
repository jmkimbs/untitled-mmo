#include <iostream>

#include "raylib.h"

#include "Game.h"
#include "src/client/ui/camera/TopCamera.h"
#include "src/client/inputhandler/InputHandler.h"


int main(void)
{
	InitWindow(1280, 720, "Untitled MMO");
	SetTargetFPS(60);

	ummo::camera::TopCamera* cam = new ummo::camera::TopCamera();
	Camera* camera = cam->GetCamera();

	ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();

	EnableCursor();
	while (!WindowShouldClose())
	{
		ih->HandleInput();
		cam->Update();

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(*camera);
				DrawCube((Vector3) { 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, RED);
				DrawCubeWires((Vector3) { 0.0f, 0.0f, 0.0f }, 2.0f, 2.0f, 2.0f, MAROON);
				DrawGrid(10, 1.0f);
			EndMode3D();

			DrawText("Welcome to the beginnings of the Untitled MMO", 400, 40, 20, LIGHTGRAY);
			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}