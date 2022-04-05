#include <filesystem>
#include "raylib.h"

namespace ummo {
	namespace common {
		namespace characters {

			enum CharacterType {
				kPlayer,
				kFriendlyNPC,
				kHostileNPC
			};

			class CharacterUtils {

				private:
					static std::filesystem::path resourcesPath;
				public:
					static void SetResourcesPath(std::filesystem::path);
					static std::filesystem::path GetModelPath(std::string);
			};
		}
	}
}