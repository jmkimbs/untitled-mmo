
#include <filesystem>
#include <iostream>
#include "raylib.h"

#include "character-utils.hpp"
#include "player.hpp"
#include "character.hpp"

namespace ummo {
	namespace common {
		namespace characters {

			Player::Player(int id) : Character(id) {
				this->InitializeModel(id);
				// this->InitializeAttributes(id);
			}

			void Player::InitializeModel(int id) {
				// Model lance = LoadModel("~/game-dev/untitled-mmo/src/client/resources/models/Lance.glb");
				std::filesystem::path modelPath = CharacterUtils::GetModelPath("Lance.glb");
				std::cout << "Found path for Lance model is '" << modelPath << "'" << std::endl;
				Model lance = LoadModel(modelPath.string().c_str());
				this->SetModel(lance);
			}
		}
	}
}