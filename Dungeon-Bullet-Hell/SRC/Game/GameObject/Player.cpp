#include "../Game.h"
#include "Player.h"

#include "PlayerBullet.h"
#include "../../Engine/Utils.hpp"
#include "../../Engine/Logger.h"

#include "../../Engine/Resources/CollisionShape.h"


void Player::Ready()
{
    Logger::Log("Player ready.");

    ResourcesManager* resourcesManager = &ResourcesManager::Get();
    inputManager = &InputManager::Get();

    SpriteSheet spriteSheet("./Assets/Characters/Player.png", {16, 16});
    
    movement = &AddComponent<CharacterMovement2D>();
    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    camera = &AddComponent<Camera2D>();

    Animation animIdle({0}, spriteSheet, 1.0f);
    animatedSprite->AddAnimation("Idle", animIdle);
    Animation animWalkUp({9, 13, 17, 21}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkUp", animWalkUp);
    Animation animWalkLeft({10, 14, 18, 22}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkLeft", animWalkLeft);
    Animation animWalkRight({11, 15, 19, 23}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkRight", animWalkRight);
    Animation animWalkDown({8, 12, 16, 20}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkDown", animWalkDown);
    Animation animDash({25, 26, 27, 28}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("Dash", animDash);
    
    animatedSprite->PlayAnimation("Idle");

    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape);

    EquipGun();
}

void Player::TakeDamage(int damage)
{
    
}

void Player::EquipGun()
{
    gun = SceneTree::Get().AddGameObject<Gun>("", this);
}

void Player::Update(float deltaTime)
{
    if (isDashing)
    {
        if (SDL_GetTicks() - startDash > 100)
        {
            isDashing = false;
            movement->SetLinearVelocity(glm::vec2(0, 0));
        }
        else
        {
            movement->SetLinearVelocity(dashDir * 3000.0f);
            animatedSprite->PlayAnimation("Dash");
        }
    }
    else
    {
        moveDir = {0, 0};
        
        moveDir.x = inputManager->GetLeftStickX();
        moveDir.y = inputManager->GetLeftStickY();
        
        if (inputManager->IsActionHeld(Action::MoveLeft)) moveDir.x = -1;
        if (inputManager->IsActionHeld(Action::MoveRight)) moveDir.x = 1;
        if (inputManager->IsActionHeld(Action::MoveUp)) moveDir.y = -1;
        if (inputManager->IsActionHeld(Action::MoveDown)) moveDir.y = 1;
            
        if (moveDir == glm::vec2(0, 0)) animatedSprite->PlayAnimation("Idle");
        if (moveDir.x < 0) animatedSprite->PlayAnimation("WalkLeft");
        if (moveDir.x > 0) animatedSprite->PlayAnimation("WalkRight");
        if (moveDir.y < 0) animatedSprite->PlayAnimation("WalkUp");
        if (moveDir.y > 0) animatedSprite->PlayAnimation("WalkDown");

        if (inputManager->GetRightStickX() != 0.0f || inputManager->GetRightStickY() != 0.0f)
        {
            lookDir = glm::vec2(inputManager->GetRightStickX(), inputManager->GetRightStickY());
        } else lookDir = glm::normalize(glm::vec2(inputManager->GetMouseX() - (DISPLAY_WIDTH / 2.0f), inputManager->GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));

        if (inputManager->IsActionHeld(Action::Dash) && SDL_GetTicks() - lastDash > dashCooldown * 1000)
        {
            Logger::Log("Dash!");
            dashDir = moveDir;
            isDashing = true;
            startDash = SDL_GetTicks();
            lastDash = SDL_GetTicks();
        }
        
        movement->SetLinearVelocity(moveDir * 300.0f);
    }
    camera->OffsetPosition = lookDir * 100.0f;
}
