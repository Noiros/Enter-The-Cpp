#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Components/CharacterMovement2D.h"
#include "../../Engine/Components/AnimatedSprite2D.h"
#include "../../Engine/Components/Collider2D.h"

#include <memory>

#include "Gun.h"

class Player : public GameObject
{
public:
    InputManager* inputManager;

    int HP = 3;
    
    float dashTime = 2.0f;
    float dashCooldown = 2.5f;
    bool isDashing = false;
    
    void Update(float deltaTime);
    void Ready();
    void TakeDamage(int damage);
    void EquipGun();

private:
    CharacterMovement2D* movement;
    AnimatedSprite2D* animatedSprite;
    Camera2D* camera;
    Gun* gun;
    
    uint32_t startDash = 0;
    uint32_t lastDash = 0;
    glm::vec2 dashDir = glm::vec2(0, 0);
    glm::vec2 moveDir = glm::vec2(0, 0);
    glm::vec2 lookDir = glm::vec2(0, 0);
};
