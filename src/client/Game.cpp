#include <iostream>
#include "raylib.h"

#include "Game.h"
#include "camera/TopCamera.h"


int main(void)
{
	InitWindow(1280, 720, "Untitled MMO");
	SetTargetFPS(60);

	ummo::camera::TopCamera *cam = new ummo::camera::TopCamera();
	Camera3D camera = cam->GetCamera();

	std::cout << "x " << (cam->GetCamera()).position.x << " y " << (cam->GetCamera()).position.y << " z " << (cam->GetCamera()).position.z << std::endl;

	SetCameraMode(camera, CAMERA_FREE);

	while (!WindowShouldClose())
	{

		BeginDrawing();
			ClearBackground(RAYWHITE);

			UpdateCamera(&camera);

			BeginMode3D(camera);
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