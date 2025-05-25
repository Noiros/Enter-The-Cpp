#include "../Game.h"
#include "Player.h"

#include "Bullet.h"
#include "../../Engine/Utils.hpp"
#include "../../Engine/Logger.h"
#include "../../Engine/Components/TextureRect.h"

void Player::Shoot(glm::vec2 pos, glm::vec2 vel)
{
    Bullet* bullet = SceneTree::GetInstance().AddNode<Bullet>();
    bullet->transform->position = pos;
    bullet->transform->size = glm::vec2(8, 8);

    Logger::Log("Bullet created.");
    
    /*if (head)
    {
        Bullet* bullet = head;
        head = bullet->state.next;

        bullet->state.params.pos = pos;
        bullet->state.params.vel = vel;
        bullet->isActive = true;
    }*/
}

void Player::Ready()
{
    Logger::Log("Player ready.");

    SceneTree* sceneTree = &SceneTree::GetInstance();

    sceneTree->AddComponent<TextureRect>(this, "Ship");
    movement = sceneTree->AddComponent<Movement>(this);
}

void Player::Update(float deltaTime)
{
    glm::vec2 direction = glm::vec2(0, 0);
    
    if (InputManager::GetInstance().IsActionHeld(Action::MoveLeft)) direction.x = -1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveRight)) direction.x = 1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveUp)) direction.y = -1;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveDown)) direction.y = 1;

    if (InputManager::GetInstance().IsActionHeld(Action::Shoot)) Shoot(glm::vec2(transform->position + glm::vec2(28, 0)), glm::vec2(0, -500) + Utils::RndVec2(-50, 50));

    movement->SetLinearVelocity(direction * speed);
    
    //movement->SetLinearVelocity(glm::vec2(InputManager::GetInstance().GetLeftStickX(), InputManager::GetInstance().GetLeftStickY()) * speed * deltaTime);


    /*
    //clamp position to borders
    const float rightBorder = DISPLAY_WIDTH - transform->size.x;
    const float bottomBorder = DISPLAY_HEIGHT - transform->size.y;

    if (transform->position.x >= rightBorder) transform->position.x = rightBorder;
    else if (transform->position.x <= 0) transform->position.x = 0;
    if (transform->position.y >= bottomBorder) transform->position.y = bottomBorder;
    else if (transform->position.y <= 0) transform->position.y = 0;
    */
}
