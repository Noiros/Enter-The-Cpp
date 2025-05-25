#pragma once

#include "../Component.h"

class Component2D : public Component
{
    public:
        void Update(float deltaTime) override {};
        void Ready() override {};
        void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) override {};
    
};
