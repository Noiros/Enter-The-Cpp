#include "../Game.h"
#include "Player.h"

#include "Bullet.h"
#include "../../Engine/Utils.hpp"
#include "../../Engine/Logger.h"

void Player::Shoot()
{
    Bullet* bullet = SceneTree::GetInstance().AddNode<Bullet>();
    bullet->transform->position = transform->position;
    bullet->transform->size = glm::vec2(8, 8);
    bullet->movement->SetLinearVelocity(lookDir * 1000.0f);
}

void Player::Ready()
{
    Logger::Log("Player ready.");

    SceneTree* sceneTree = &SceneTree::GetInstance();

    textureRect = sceneTree->AddComponent<AnimatedSprite2D>(this, "Ship");
    movement = sceneTree->AddComponent<CharacterMovement2D>(this);
    camera = sceneTree->AddComponent<Camera2D>(this);
}

void Player::Update(float deltaTime)
{
    moveDir = {0, 0};
    if (InputManager::GetInstance().IsActionHeld(Action::MoveLeft)) moveDir.x = -1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveRight)) moveDir.x = 1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveUp)) moveDir.y = -1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveDown)) moveDir.y = 1;

    if (InputManager::GetInstance().IsActionHeld(Action::Shoot)) Shoot();

    lookDir = glm::normalize(glm::vec2(InputManager::GetInstance().GetMouseX() - (DISPLAY_WIDTH / 2.0f), InputManager::GetInstance().GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));
    
    transform->rotation = glm::degrees(std::atan2(lookDir.y, lookDir.x)) + 90.0f;
    movement->SetLinearVelocity(moveDir * speed);
}
