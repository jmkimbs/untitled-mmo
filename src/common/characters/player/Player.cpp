
#include "raylib.h"

#include "Player.h"
#include "src/common/characters/Character.h"

namespace ummo {
	namespace common {
		namespace characters {

			Player::Player(int id) : Character(id) {
				this->InitializeModel(id);
				// this->InitializeAttributes(id);
			}

			void Player::InitializeModel(int id) {
				// Model lance = LoadModel("~/game-dev/untitled-mmo/src/client/resources/models/Lance.glb");
				Model lance = LoadModel("./src/client/resources/models/Lance.glb");
				this->SetModel(lance);
			}
		}
	}
}