#pragma once

#include <SDL_render.h>
#include "../Component.h"

class TextureRect : public Component
{
    public:    
        SDL_Texture* texture;
        uint32_t animSpeed;

        TextureRect(SDL_Texture* tex) : texture(tex) {}
        ~TextureRect() override = default;

        void Update(float deltaTime) override;
        void Ready() override;
        void Render(SDL_Renderer* renderer) override;
};
