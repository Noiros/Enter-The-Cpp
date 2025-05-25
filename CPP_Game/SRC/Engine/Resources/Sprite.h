#pragma once
#include <SDL_render.h>
#include <string_view>
#include "../Modules/ResourcesManager.h"

class Sprite
{
public:
    Sprite(std::string_view textureName) : textureName(textureName)
    {
        texture = ResourcesManager::GetInstance().GetTexture(textureName);
    };
    
    std::string_view textureName;
    SDL_Texture* texture;
};
