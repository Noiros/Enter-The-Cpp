#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Components/CharacterMovement2D.h"
#include "../../Engine/Components/AnimatedSprite2D.h"

class EnemyBullet : public GameObject
{    
public:
    float bulletSpeed = 1.0f;
    
    EnemyBullet(glm::vec2 dir, GameObject* s) : direction(dir), shooterObject(s) {}
    
    void Ready() override;
    void HitObject(GameObject* other) override;

    AnimatedSprite2D* animatedSprite = nullptr;
    GameObject* shooterObject = nullptr;
    CharacterMovement2D* movement = nullptr;
    glm::vec2 direction = {0, 0};
};