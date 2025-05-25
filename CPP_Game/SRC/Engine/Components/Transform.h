#pragma once

#include <vec2.hpp>

#include "../Component.h"

class Transform : public Component
{
    public:
        glm::vec2 position;
        glm::vec2 scale;
        glm::vec2 rotation;
        glm::vec2 size = {64, 64};

        Transform() = default;
        ~Transform() override = default;

        void Update(float deltaTime) override;
        void Ready() override;
        void Render(SDL_Renderer* renderer) override;
};
