#include "ResourcesManager.h"
#include "../Logger.h"
#include <SDL_image.h>

#include "RenderingServer.h"

ResourcesManager* ResourcesManager::s_instance = nullptr;

ResourcesManager::ResourcesManager()
{
    Logger::Log("AssetManager constructor called");
}

ResourcesManager::~ResourcesManager()
{
    ClearAssets();
    Logger::Log("AssetManager destructor called");
}

void ResourcesManager::ClearAssets()
{
    for (auto [name, texture] : textures) //key, value
    {
        SDL_DestroyTexture(texture);
    }
    textures.clear();
}

void ResourcesManager::AddTexture(std::string_view fileName)
{
    SDL_Texture* texture = IMG_LoadTexture(RenderingServer::GetInstance().GetRenderer(), fileName.data());
    //get the raw const char*
    if (texture)
    {
        textures.emplace(fileName, texture);
        Logger::Log("New texture added to the assetManager: " + static_cast<std::string>(fileName));
    }
    else Logger::Err("Canot find file: " + static_cast<std::string>(fileName));
}

SDL_Texture* ResourcesManager::GetTexture(std::string_view fileName)
{
    if (!textures.contains(fileName))
    {
        SDL_Texture* texture = IMG_LoadTexture(RenderingServer::GetInstance().GetRenderer(), fileName.data());
        textures.emplace(fileName, texture);
    }
    return textures.at(fileName);
}
