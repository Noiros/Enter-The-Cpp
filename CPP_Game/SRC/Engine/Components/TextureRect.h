#pragma once

#include <SDL_render.h>
#include <string_view>

#include "../Component.h"

class TextureRect : public Component
{
public:
    SDL_Texture* texture;
    uint32_t animSpeed;

    TextureRect(std::string_view name);
    ~TextureRect() override = default;

    void Update(float deltaTime) override;
    void Ready() override;
    void Render(SDL_Renderer* renderer) override;
};
