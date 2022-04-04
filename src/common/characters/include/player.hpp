#pragma once

#include "raylib.h"

#include "character.hpp"

namespace ummo {
	namespace common {
		namespace characters {

			class Player : public Character {

				private:
					void InitializeModel(int);
					void InitializeAttributes(int);


				public:
					Player(int);
					~Player() = default;


			};
		}
	}
}