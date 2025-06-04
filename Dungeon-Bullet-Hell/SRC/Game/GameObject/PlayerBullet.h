#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Components/CharacterMovement2D.h"

class PlayerBullet : public GameObject
{    
public:
    float bulletSpeed = 2.0f;
    
    PlayerBullet(glm::vec2 dir, GameObject* s) : direction(dir), shooterObject(s) {};
    
    void Ready() override;
    void HitObject(GameObject* other) override;

    GameObject* shooterObject;
    CharacterMovement2D* movement;
    glm::vec2 direction;
};