#pragma once

#include <SDL.h>
#include <vec2.hpp>

class Component
{
public:
    virtual ~Component() = default; // Destructeur virtuel pour permettre dynamic_cast
    virtual void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Ready() = 0;
    
    int ZOrder = 0;
};
