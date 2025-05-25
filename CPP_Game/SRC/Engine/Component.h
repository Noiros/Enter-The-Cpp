#pragma once

#include <SDL.h>


class Node;

class Component
{
        public:
                virtual ~Component() = default; // Destructeur virtuel pour permettre dynamic_cast
                virtual void Render(SDL_Renderer* renderer) = 0;
                virtual void Update(float deltaTime) = 0;
                virtual void Ready() = 0;

                Node* ParentNode;
};
