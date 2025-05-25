#pragma once
#include <vec2.hpp>
#include "../Component.h"

class Movement : public Component
{
    public:
        Movement(glm::vec2 baseVelocity = {0, 0}) : velocity(baseVelocity) {}
        ~Movement() = default;

        void AddLinearVelocity(glm::vec2 vel) { velocity += vel; }
        void SetLinearVelocity(glm::vec2 vel) { velocity = vel; }
        glm::vec2 GetLinearVelocity() { return velocity; }

        void Update(float deltaTime) override;
        void Ready() override {}
        void Render(SDL_Renderer* renderer) override {}

    private:
        glm::vec2 velocity;
};
