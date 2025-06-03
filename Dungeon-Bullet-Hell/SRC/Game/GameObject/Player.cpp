#include "../Game.h"
#include "Player.h"

#include "Bullet.h"
#include "Empty.h"
#include "../../Engine/Utils.hpp"
#include "../../Engine/Logger.h"

#include "../../Engine/Components/Transform2D.h"
#include "../../Engine/Resources/CollisionShape.h"

void Player::Shoot()
{
    Empty* bullet = SceneTree::Get().AddGameObject<Empty>();
    //Transform2D* bulletTransform = &bullet->GetComponent<Transform2D>();
    //bulletTransform->position = GetComponent<Transform2D>().position;
    //bulletTransform->size = glm::vec2(64, 64);
    //bullet->movement->SetLinearVelocity(lookDir * 1000.0f);
}

void Player::Ready()
{
    Logger::Log("Player ready.");

    ResourcesManager* resourcesManager = &ResourcesManager::Get();

    SpriteSheet spriteSheet("./Assets/Images/Characters/Skeleton.png", {16, 16});
    
    movement = &AddComponent<CharacterMovement2D>();
    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    AddComponent<Camera2D>();

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

    CollisionShape collisionShape;
    AddComponent<Collider2D>(collisionShape);
}

void Player::Update(float deltaTime)
{

    moveDir = {0, 0};
    if (InputManager::Get().IsActionHeld(Action::MoveLeft))
    {
        moveDir.x = -1;
        animatedSprite->PlayAnimation("WalkLeft");
    }
    if (InputManager::Get().IsActionHeld(Action::MoveRight))
    {
        moveDir.x = 1;
        animatedSprite->PlayAnimation("WalkRight");
    }
    if (InputManager::Get().IsActionHeld(Action::MoveUp))
    {
        moveDir.y = -1;
        animatedSprite->PlayAnimation("WalkUp");
    }
    if (InputManager::Get().IsActionHeld(Action::MoveDown))
    {
        moveDir.y = 1;
        animatedSprite->PlayAnimation("WalkDown");
    }
    if (moveDir == glm::vec2(0, 0)) animatedSprite->PlayAnimation("Idle");

    
    if (InputManager::Get().IsActionHeld(Action::Shoot)) Shoot();

    lookDir = glm::normalize(glm::vec2(InputManager::Get().GetMouseX() - (DISPLAY_WIDTH / 2.0f), InputManager::Get().GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));
    
    //transform->rotation = glm::degrees(std::atan2(lookDir.y, lookDir.x)) + 90.0f;
    movement->SetLinearVelocity(moveDir * 300.0f);
}
