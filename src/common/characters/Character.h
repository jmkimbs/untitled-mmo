#pragma once

#include "raylib.h"

namespace ummo {
	namespace common {
		namespace characters {

			enum CharacterType {
				kPlayer,
				kFriendlyNPC,
				kHostileNPC
			};

			class Character {

				private:
					Model model;
					Vector3 position;
					float rotation;

					// virtual void InitializeModel(int) = 0;
					// virtual void InitializeAttributes(int) = 0;

				public:
					Character(int);
					~Character();
					Model GetModel();
					void SetModel(Model);
					Vector3 GetPosition();
					Vector3& GetLivePosition();
					float GetRotation();
					void Move(Vector3);
					void SetPosition(Vector3);
					void Rotate(float);
					void SetRotation(float);

			};
		}
	}
}