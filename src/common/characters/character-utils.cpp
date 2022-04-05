#include <filesystem>
#include "raylib.h"

#include "character-utils.hpp"

std::filesystem::path ummo::common::characters::CharacterUtils::resourcesPath = std::filesystem::path(".");

void ummo::common::characters::CharacterUtils::SetResourcesPath(std::filesystem::path path) {
	resourcesPath = path;
}

std::filesystem::path ummo::common::characters::CharacterUtils::GetModelPath(std::string modelName) {
	return std::filesystem::path(resourcesPath.string() + "models/" + modelName);
}
