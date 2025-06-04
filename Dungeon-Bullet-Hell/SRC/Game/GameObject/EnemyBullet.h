#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Components/CharacterMovement2D.h"

class EnemyBullet : public GameObject
{    
public:
    float bulletSpeed = 1.0f;
    
    EnemyBullet(glm::vec2 dir, GameObject* s) : direction(dir), shooterObject(s) {};
    
    void Ready() override;
    void HitObject(GameObject* other) override;

    GameObject* shooterObject;
    CharacterMovement2D* movement;
    glm::vec2 direction;
};