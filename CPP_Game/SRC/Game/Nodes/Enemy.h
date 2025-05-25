#pragma once
#include "../../Engine/Node.h"
#include "../../Engine/Components/AnimatedSprite2D.h"
#include "../../Engine/Components/NavAgent2D.h"

class Enemy : public Node
{
    public:
        void Update(float deltaTime) override {};
        void Ready() override;
};
