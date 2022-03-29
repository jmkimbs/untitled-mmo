#pragma once

#include "src/common/characters/player/Player.h"

namespace ummo {
	namespace client {
		namespace characters {

			class ClientPlayer : public ummo::common::characters::Player {
				private:

				public:
					ClientPlayer(int);
					void RegisterClientInputHandlers();
					~ClientPlayer() = default;

			};
		}
	}
}