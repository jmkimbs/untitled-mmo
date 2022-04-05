#pragma once

#include "raylib.h"

namespace ummo {
	namespace common {
		namespace characters {
			class Character {

				private:
					Model model;
					Vector3 position;
					Vector3 targetPosition;
					float rotation;

					Model map;

					// virtual void InitializeModel(int) = 0;
					// virtual void InitializeAttributes(int) = 0;

				public:
					Character(int);
					void InitializeAttributes(int);
					~Character();
					Model GetModel();
					void SetModel(Model);
					Vector3 GetPosition();
					Vector3& GetLivePosition();
					Vector3 GetTargetPosition();
					float GetRotation();
					void Move(Vector3);
					void MoveTo(Vector3);
					void SetPosition(Vector3);
					void Rotate(float);
					void SetRotation(float);

					void SetMap(Model);
					Model GetMap();

					void Update(float timeDelta);

			};
		}
	}
}