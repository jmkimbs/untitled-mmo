#include <iostream>

#include "raylib.h"

#include "Game.h"
#include "src/client/ui/camera/TopCamera.h"
#include "src/client/inputhandler/InputHandler.h"
#include "src/common/characters/Character.h"
#include "src/client/characters/player/ClientPlayer.h"
#include "src/client/characters/player/PlayerControls.h"


int main(void)
{
	InitWindow(1280, 720, "Untitled MMO");
	SetTargetFPS(60);

	ummo::camera::TopCamera* cam = new ummo::camera::TopCamera();
	Camera* camera = cam->GetCamera();

	ummo::input::InputHandler* ih = ummo::input::InputHandler::GetInstance();

	EnableCursor();
	// Model lance = LoadModel("./src/client/resources/models/Lance.glb");
	ummo::client::characters::ClientPlayer* lance = new ummo::client::characters::ClientPlayer(1);
	std::cout << "Get working directory" << std::endl;
	std::cout << GetWorkingDirectory() << std::endl;

	Vector3& lancePos = lance->GetLivePosition();
	ummo::client::characters::PlayerControls::RegisterInputHandlers(*lance, *camera);
	Model plane = LoadModelFromMesh(GenMeshPlane(200, 200, 50, 50));
	lance->SetMap(plane);
	
	cam->SetLiveTarget(lancePos);

	while (!WindowShouldClose())
	{

		float timeDelta = GetFrameTime();
		// lance->Move((Vector3) { 0.0f, 0.0f, -1.0f });
		ih->HandleInput();
		cam->Update();
		lance->Update(timeDelta);

		BeginDrawing();
			ClearBackground(RAYWHITE);

			BeginMode3D(*camera);
				// DrawModelEx(lance, (Vector3) { 0.0f, 0.0f, 0.0f }, (Vector3) { 1.0f, 0.0f, 0.0f }, 0.0f, (Vector3) { 2.0f, 2.0f, 2.0f }, WHITE);
				// DrawModel(lance->GetModel(), lancePos, 1, WHITE);
				DrawModelEx(lance->GetModel(), lancePos, (Vector3) { 0.0f, 1.0f, 0.0f }, lance->GetRotation(), (Vector3) { 1.0f, 1.0f, 1.0f }, WHITE);

				// plane = LoadModelFromMesh(GenMeshPlane(100, 100, 50, 50));
				// lance->SetMap(plane);
				DrawModel(plane, (Vector3) { 0.0f, 0.0f, 0.0f }, 1.0f, WHITE);
				// DrawModelWires(plane, lancePos, 1.0f, BLUE);

				// DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x + 100.0f, lancePos.y, lancePos.z }, RED);
				// DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x, lancePos.y + 100.0f, lancePos.z }, GREEN);
				// DrawLine3D((Vector3) { lancePos.x, lancePos.y, lancePos.z }, (Vector3) { lancePos.x, lancePos.y, lancePos.z + 100.0f }, BLUE);
				
				DrawLine3D((Vector3) { 0.0f, 1.0f, 0.0f }, (Vector3) { 1000.0f, 1.0f, 0.0f }, RED);
				DrawLine3D((Vector3) { 0.0f, 1.0f, 0.0f }, (Vector3) { 0.0f, 1000.0f, 0.0f }, GREEN);
				DrawLine3D((Vector3) { 0.0f, 1.0f, 0.0f }, (Vector3) { 0.0f, 1.0f, 1000.0f }, BLUE);
				
				DrawGrid(100, 1.0f);
			EndMode3D();

			DrawText("Welcome to the beginnings of the Untitled MMO", 400, 40, 20, LIGHTGRAY);
			DrawFPS(10, 10);
		EndDrawing();
	}

	UnloadModel(plane);
	CloseWindow();

	return 0;
}