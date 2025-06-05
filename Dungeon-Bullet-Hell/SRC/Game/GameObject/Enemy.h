#pragma once
#include "Player.h"
#include "../../Engine/GameObject.h"

class Enemy : public GameObject
{
    public:
        ~Enemy() { SceneTree::Get().DestroyGameObject(gun); }
    
        void Update(float deltaTime);
        void Ready();
        void EquipGun();
        void TakeDamage(int damage);

        bool roomActive = false;

        int HP = 3;
    
        float viewDistance = 1500.0f;
        float attackDistance = 300.0f;

protected:
    Player* player = nullptr;
    CharacterMovement2D* movement = nullptr;
    AnimatedSprite2D* animatedSprite = nullptr;
    Gun* gun = nullptr;
};
