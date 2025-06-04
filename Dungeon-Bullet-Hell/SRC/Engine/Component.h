#pragma once
#include <SDL_render.h>
#include <glm.hpp>

class GameObject;

class Component
{
    public:
        Component() = default;
        virtual ~Component() = default;

        GameObject* gameObject;

        virtual void Ready() {}
        virtual void Update(float deltaTime) {}
        virtual void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) {}
};

