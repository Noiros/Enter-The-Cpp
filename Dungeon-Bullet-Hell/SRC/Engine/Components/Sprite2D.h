#pragma once

#include <SDL_render.h>
#include "../Resources/Sprite.h"

#include "Component2D.h"
#include "Transform2D.h"

class Sprite2D : public Component2D
{
public:
    Sprite2D(Sprite s) : sprite(s) {};

    bool HFlip = false;
    bool VFlip = false;
    
    void Ready();
    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);
    const SDL_Point GetTextureSize();

private:
    Sprite sprite;
    SDL_Rect textureSrc;
    SDL_Texture* texture;
    Transform2D* transform;
};
