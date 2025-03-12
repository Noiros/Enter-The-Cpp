#include "ResourcesManager.h"
#include "Logger.h"
#include <SDL_image.h>

ResourcesManager::ResourcesManager(SDL_Renderer* renderer) {
	this->renderer = renderer;
	Logger::Log("Resource Manager constructor called");
}

ResourcesManager::~ResourcesManager() {
	ClearAssets();
	Logger::Log("Resource Manager destructor called");
}

void ResourcesManager::ClearAssets() {
	for (auto [path, texture] : textures) {
		SDL_DestroyTexture(texture);
	}
	textures.clear();
	Logger::Log("Resource Manager cleared");
}

void ResourcesManager::LoadTexture(std::string_view path) {
	if (!textures.contains(path)) {
		SDL_Texture* texture = IMG_LoadTexture(renderer, path.data());
		if (texture) {
			textures.emplace(path, texture);
		} else {
			Logger::Err("Texture not finded : " + static_cast<std::string>(path));
		}
	}
}

SDL_Texture* ResourcesManager::GetTexture(std::string_view path) const {
	return textures.at(path);
}