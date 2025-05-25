#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>

class ResourcesManager
{
    public:
        ResourcesManager(SDL_Renderer* renderer);
        ~ResourcesManager();

        void ClearAssets();
        void AddTexture(std::string_view name, std::string_view fileName);
        SDL_Texture* GetTexture(std::string_view name) const;

    private:
        SDL_Renderer* renderer;
        std::unordered_map<std::string_view, SDL_Texture*> textures;
        //add maps for fonts, audio...
};
