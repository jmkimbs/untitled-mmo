#pragma once

#include "raylib.h"

#include "src/common/characters/Character.h"

namespace ummo {
	namespace common {
		namespace characters {

			class Player : public Character {

				private:
					void InitializeModel(int);
					void InitializeAttributes(int);


				public:
					Player(int);
					~Player();


			};
		}
	}
}