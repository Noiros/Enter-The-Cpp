#pragma once

#include "../../Engine/GameObject.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Components/CharacterMovement2D.h"
#include "../../Engine/Components/AnimatedSprite2D.h"
#include "../../Engine/Components/Collider2D.h"

#include <memory>

class Player : public GameObject
{
public:
    InputManager* inputManager;
    
    void Update(float deltaTime);
    void Ready();

    void Shoot();

private:
    CharacterMovement2D* movement;
    AnimatedSprite2D* animatedSprite;
    Camera2D* camera;
    
    glm::vec2 moveDir = glm::vec2(0, 0);
    glm::vec2 lookDir = glm::vec2(0, 0);
};
