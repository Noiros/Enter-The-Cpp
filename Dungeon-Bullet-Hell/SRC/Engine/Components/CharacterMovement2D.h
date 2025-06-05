#pragma once
#include <vec2.hpp>
#include "Component2D.h"
#include "Transform2D.h"

class CharacterMovement2D : public Component2D
{
public:
    CharacterMovement2D(glm::vec2 baseVelocity = {0, 0}) : velocity(baseVelocity) {}
    ~CharacterMovement2D() {}

    void AddLinearVelocity(glm::vec2 vel) { velocity += vel; }
    void SetLinearVelocity(glm::vec2 vel) { velocity = vel; }
    glm::vec2 GetLinearVelocity() { return velocity; }

    void Update(float deltaTime);
    void Ready();

private:
    glm::vec2 velocity;
    Transform2D* transform;
};
