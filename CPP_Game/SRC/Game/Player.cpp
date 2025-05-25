#include "Game.h"
#include "Player.h"

#include "bullet.h"
#include "../Engine/Utils.hpp"
#include "../Engine/Logger.h"
#include "../Engine/Components/TextureRect.h"

/*void Player::Shoot(vec2 pos, vec2 vel)
{
    if (head)
    {
        Bullet* bullet = head;
        head = bullet->state.next;

        bullet->state.params.pos = pos;
        bullet->state.params.vel = vel;
        bullet->isActive = true;
    }
}*/

void Player::Ready()
{    
    Logger::Log("Player ready.");
    
    SceneTree* sceneTree = &SceneTree::GetInstance();
    
    sceneTree->AddComponent<TextureRect>(this, ResourcesManager::GetInstance().GetTexture("Ship"));
}

void Player::Update(float deltaTime)
{
    Logger::Log("Player update.");
    
    if (InputManager::GetInstance().IsActionHeld(Action::MoveLeft)) transform->position.x -= speed * deltaTime;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveRight)) transform->position.x += speed * deltaTime;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveUp)) transform->position.y -= speed * deltaTime;
    if (InputManager::GetInstance().IsActionHeld(Action::MoveDown)) transform->position.y += speed * deltaTime;

    //if (input->IsActionHeld(Action::Shoot)) Shoot(vec2(pos + vec2(28, 0)), vec2(0, -500) + Utils::RndVec2(-50, 50));

    transform->position.x += InputManager::GetInstance().GetLeftStickX() * speed * deltaTime;
    transform->position.y += InputManager::GetInstance().GetLeftStickY() * speed * deltaTime;

    //clamp position to borders
    const float rightBorder = DISPLAY_WIDTH - transform->size.x;
    const float bottomBorder = DISPLAY_HEIGHT - transform->size.y;

    if (transform->position.x >= rightBorder) transform->position.x = rightBorder;
    else if (transform->position.x <= 0) transform->position.x = 0;
    if (transform->position.y >= bottomBorder) transform->position.y = bottomBorder;
    else if (transform->position.y <= 0) transform->position.y = 0;
}