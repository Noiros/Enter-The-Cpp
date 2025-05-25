#include "../Game.h"
#include "Player.h"

#include "Bullet.h"
#include "../../Engine/Utils.hpp"
#include "../../Engine/Logger.h"

void Player::Shoot()
{
    Bullet* bullet = SceneTree::GetInstance().AddNode<Bullet>();
    bullet->transform->position = transform->position;
    bullet->transform->size = glm::vec2(64, 64);
    bullet->movement->SetLinearVelocity(lookDir * 1000.0f);
}

void Player::Ready()
{
    Logger::Log("Player ready.");

    SceneTree* sceneTree = &SceneTree::GetInstance();
    ResourcesManager* resourcesManager = &ResourcesManager::GetInstance();
    
    movement = sceneTree->AddComponent<CharacterMovement2D>(this);
    camera = sceneTree->AddComponent<Camera2D>(this);

    SpriteSheet spriteSheet("./Assets/Images/Characters/Skeleton.png", {16, 16});
    
    animatedSprite = sceneTree->AddComponent<AnimatedSprite2D>(this, spriteSheet);
    
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
    
    animatedSprite->PlayAnimation("Idle");
    
}

void Player::Update(float deltaTime)
{
    moveDir = {0, 0};
    if (InputManager::GetInstance().IsActionHeld(Action::MoveLeft))
    {
        moveDir.x = -1;
        animatedSprite->PlayAnimation("WalkLeft");
    }
    if (InputManager::GetInstance().IsActionHeld(Action::MoveRight))
    {
        moveDir.x = 1;
        animatedSprite->PlayAnimation("WalkRight");
    }
    if (InputManager::GetInstance().IsActionHeld(Action::MoveUp))
    {
        moveDir.y = -1;
        animatedSprite->PlayAnimation("WalkUp");
    }
    if (InputManager::GetInstance().IsActionHeld(Action::MoveDown))
    {
        moveDir.y = 1;
        animatedSprite->PlayAnimation("WalkDown");
    }

    if (InputManager::GetInstance().IsActionHeld(Action::Shoot)) Shoot();

    lookDir = glm::normalize(glm::vec2(InputManager::GetInstance().GetMouseX() - (DISPLAY_WIDTH / 2.0f), InputManager::GetInstance().GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));
    
    //transform->rotation = glm::degrees(std::atan2(lookDir.y, lookDir.x)) + 90.0f;
    movement->SetLinearVelocity(moveDir * 300.0f);
}
