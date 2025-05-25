#pragma once

#include <SDL_render.h>
#include "../Resources/Sprite.h"

#include "Component2D.h"

class Sprite2D : public Component2D
{
public:
    Sprite2D(Sprite s) : sprite(s) {};
    
    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);

protected:
    Sprite sprite;
    SDL_Rect textureSrc;
    SDL_Texture* texture;
};
