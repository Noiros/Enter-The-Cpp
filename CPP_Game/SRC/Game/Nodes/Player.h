#pragma once

#include "../../Engine/Node.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Components/Movement.h"
#include <memory>

class Player : public Node
{
public:
    float speed = 100.0f;
    int animSpeed; //frames per second

    InputManager* inputManager;

    void Update(float deltaTime) override;
    void Ready() override;

    void Shoot(glm::vec2 pos, glm::vec2 vel);

private:
    Movement* movement;
};
