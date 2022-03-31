#pragma once
#include <map>
#include "raylib.h"

#include "src/client/characters/player/ClientPlayer.h"
#include "src/common/characters/player/Player.h"

namespace ummo {
	namespace client {
		namespace characters {
			
			class PlayerControls { // : CharacterControls ? or assume characters never get controlled so... why bother? if w
				private:
					static void RegisterMovementInputHandlers(ummo::common::characters::Player&, Camera&); // wasd, clicking around the character, etc.
					static void MovementKeydownHandler(std::map<KeyboardKey, bool>, ummo::common::characters::Player&);
					static void MouseClickHandler(Vector2, ummo::common::characters::Player&, Camera&);

					static void RegisterGuildInputHandlers(ummo::common::characters::Player&); // clicking buttons etc.
					static void RegisterInventoryHandlers(ummo::common::characters::Player&); // handling dropping, deleting, locking
					static void RegisterSkillManagerHandler(ummo::common::characters::Player&); // handling using skills, skills to skillbar, skill levels

					static void RegisterModalInputHandlers(ummo::common::characters::Player&); // e.g. open friends modal, open guild modal, open inventory modal
				
				public:
					PlayerControls() = default;
					~PlayerControls() = default;

					static void RegisterInputHandlers(ummo::common::characters::Player&, Camera&);
			};

		}
	}
}