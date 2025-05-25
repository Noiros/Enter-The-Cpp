#pragma once

#include <SDL_render.h>
#include <string_view>

#include "Component2D.h"

class Sprite2D : public Component2D
{
public:
    SDL_Texture* texture;
    uint32_t animSpeed;

    Sprite2D(std::string_view name);

    void Update(float deltaTime);
    void Ready();
    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);
};
