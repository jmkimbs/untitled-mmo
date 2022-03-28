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
				public:
					Character(int id, CharacterType type);
					~Character() = default;
					Model GetModel();
					Vector3 GetPosition();
					float GetRotation();
					void MoveTo(Vector3 newPosition);

			};
		}
	}
}