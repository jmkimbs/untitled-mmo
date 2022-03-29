#include "src/client/characters/player/PlayerControls.h"
#include "src/common/characters/player/Player.h"


namespace ummo {
	namespace client {
		namespace characters {

			ClientPlayer::ClientPlayer(int id) : Player(id) {

			}

			void ClientPlayer::RegisterClientInputHandlers() {

				ummo::client::characters::PlayerControls::RegisterInputHandlers(*this);

			}

		}
	}
}