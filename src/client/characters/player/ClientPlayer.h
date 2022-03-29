#pragma once

#include "src/common/characters/player/Player.h"

namespace ummo {
	namespace client {
		namespace characters {

			class ClientPlayer : ummo::common::characters::Player {
				private:

				public:
					ClientPlayer(int);
					void RegisterClientInputHandlers();

			};
		}
	}
}