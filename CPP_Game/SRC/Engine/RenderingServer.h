#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>
#include "Component.h"


class RenderingServer
{
    public:    
        void Render();
        void AddComponent(Component* component);
        void RemoveComponent(Component* component);

        void Setup();
        void Clear();

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
};
