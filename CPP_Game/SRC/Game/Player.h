#pragma once

#include "../Engine/Node.h"
#include "../Engine/Engine.h"
#include <memory>

class Player : public Node
{
    public:
        float speed;
        int animSpeed; //frames per second
        //std::unique_ptr<InputManager>& input;

        Player() = default;
        ~Player() override = default;

        void Update(float deltaTime);
        void Ready();

        //void Shoot(vec2 pos, vec2 vel);
};
