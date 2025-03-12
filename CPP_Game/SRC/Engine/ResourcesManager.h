#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>


class ResourcesManager {
public:
	ResourcesManager(SDL_Renderer* renderer);
	~ResourcesManager();

	void ClearAssets();
	void LoadTexture(std::string_view path);
	SDL_Texture* GetTexture(std::string_view path) const;

private:
	SDL_Renderer* renderer;
	std::unordered_map<std::string_view, SDL_Texture*> textures;
};