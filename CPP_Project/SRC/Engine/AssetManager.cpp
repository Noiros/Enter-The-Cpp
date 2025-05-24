#include "AssetManager.h"
#include "Logger.h"
#include <SDL_image.h>

AssetManager::AssetManager(SDL_Renderer* renderer)
{
	this->renderer = renderer;
	Logger::Log("AssetManager constructor called");
}

AssetManager::~AssetManager()
{
	ClearAssets();
	Logger::Log("AssetManager destructor called");
}

void AssetManager::ClearAssets()
{
	for (auto [name, texture] : textures) //key, value
	{
		SDL_DestroyTexture(texture);
	}
	textures.clear();
}

void AssetManager::AddTexture(std::string_view name, std::string_view fileName)
{
	SDL_Texture* texture = IMG_LoadTexture(renderer, fileName.data()); //get the raw const char*
	if (texture)
	{
		textures.emplace(name, texture);
		Logger::Log("New texture added to the assetManager: " + static_cast<std::string>(name));
	}
	else Logger::Err("Canot find file: " + static_cast<std::string>(fileName));
}

SDL_Texture* AssetManager::GetTexture(std::string_view name) const
{
	return textures.at(name);
}

