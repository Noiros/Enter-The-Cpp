#pragma once

#include <vec2.hpp>

#include "../Component.h"

class Transform : public Component
{
public:
    glm::vec2 position;
    glm::vec2 anchor = {0.5f, 0.5f};
    glm::vec2 scale;
    glm::vec2 size = {64, 64};
    float rotation;

    Transform(glm::vec2 pos = {0, 0}, glm::vec2 scale = {1, 1}, float rot = 0.0f) :  position(pos), scale(scale), rotation(rot) {}
    ~Transform() override = default;

    void Update(float deltaTime) override;
    void Ready() override;
    void Render(SDL_Renderer* renderer) override;
};
