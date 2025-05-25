#pragma once

#include "../Engine/Node.h"
#include "../Engine/Engine.h"
#include <memory>

class Player : public Node
{
public:
    float speed = 100.0f;
    int animSpeed; //frames per second

    InputManager* inputManager;

    ~Player() override = default;

    void Update(float deltaTime) override;
    void Ready() override;

    //void Shoot(vec2 pos, vec2 vel);
};
