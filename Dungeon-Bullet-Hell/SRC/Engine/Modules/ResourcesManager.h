#pragma once
#include <SDL.h>
#include <unordered_map>
#include <string>

class ResourcesManager
{
public:
    ResourcesManager();
    ~ResourcesManager();

    static void SetInstance(ResourcesManager* instance) { s_instance = instance; }
    static ResourcesManager& Get() { return *s_instance; }
    ResourcesManager(const ResourcesManager&) = delete;
    ResourcesManager& operator=(const ResourcesManager&) = delete;

    void ClearAssets();
    void AddTexture(std::string_view fileName);
    SDL_Texture* GetTexture(std::string_view fileName);

private:
    static ResourcesManager* s_instance;
    std::unordered_map<std::string_view, SDL_Texture*> textures;
    //add maps for fonts, audio...
};
