#include <iostream>

#include "raylib.h"

#include "Game.h"
#include "src/client/ui/camera/TopCamera.h"
#include "src/client/inputhandler/InputHandler.h"
#include "src/common/characters/Character.h"
#include "src/common/characters/player/Player.h"


int main(void)
{
	InitWindow(1280, 720, "Untitled MMO");
	SetTargetFPS(60);

	ummo::camera::TopCamera* cam = new ummo::camera::TopCamera();
	Camera* camera = cam->GetCamera();

	ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();

	EnableCursor();
	// Model lance = LoadModel("./src/client/resources/models/Lance.glb");
	ummo::common::characters::Character* lance = new ummo::common::characters::Player(1);
	std::cout << "Get working directory" << std::endl;
	std::cout << GetWorkingDirectory() << std::endl;

	Vector3& lancePos = lance->GetLivePosition();
	cam->SetLiveTarget(lancePos);

	while (!WindowShouldClose())
	{
		lance->Move((Vector3) { 0.0f, 0.0f, -1.0f });
		ih->HandleInput();
		cam->Update();

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(*camera);
				// DrawModelEx(lance, (Vector3) { 0.0f, 0.0f, 0.0f }, (Vector3) { 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3) { 2.0f, 2.0f, 2.0f }, WHITE);
				DrawModel(lance->GetModel(), lancePos, 1, WHITE);

				DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x + 100.0f, lancePos.y, lancePos.z }, RED);
				DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x, lancePos.y + 100.0f, lancePos.z }, GREEN);
				DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x, lancePos.y, lancePos.z + 100.0f }, BLUE);
				
				DrawGrid(10, 1.0f);
			EndMode3D();

			DrawText("Welcome to the beginnings of the Untitled MMO", 400, 40, 20, LIGHTGRAY);
			DrawFPS(10, 10);
		EndDrawing();
	}

	CloseWindow();

	return 0;
}