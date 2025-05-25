#pragma once

#include "../Component.h"

class ComponentUI : public Component
{
public:
    void Update(float deltaTime) override {};
    void Ready() override {};
    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) override {};
    
};
