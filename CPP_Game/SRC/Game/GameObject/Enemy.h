#pragma once
#include "Player.h"
#include "../../Engine/GameObject.h"

class Enemy : public GameObject
{
    public:
        void Update(float deltaTime);
        void Ready();

private:
    Player* player;
    CharacterMovement2D* movement;
    AnimatedSprite2D* animatedSprite;
    Transform2D* transform;
};
