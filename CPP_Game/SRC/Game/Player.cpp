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

void Player::Update(float deltaTime)
{
    Logger::Log("Player update.");
    
    /*if (input->IsActionHeld(Action::MoveLeft)) transform->position.x -= speed * deltaTime;
    if (input->IsActionHeld(Action::MoveRight)) transform->position.x += speed * deltaTime;
    if (input->IsActionHeld(Action::MoveUp)) transform->position.y -= speed * deltaTime;
    if (input->IsActionHeld(Action::MoveDown)) transform->position.y += speed * deltaTime;
    //if (input->IsActionHeld(Action::Shoot)) Shoot(vec2(pos + vec2(28, 0)), vec2(0, -500) + Utils::RndVec2(-50, 50));

    transform->position.x += input->GetLeftStickX() * speed * deltaTime;
    transform->position.y += input->GetLeftStickY() * speed * deltaTime;

    //clamp position to borders
    const float rightBorder = DISPLAY_WIDTH - transform->size.x;
    const float bottomBorder = DISPLAY_HEIGHT - transform->size.y;

    if (transform->position.x >= rightBorder) transform->position.x = rightBorder;
    else if (transform->position.x <= 0) transform->position.x = 0;
    if (transform->position.y >= bottomBorder) transform->position.y = bottomBorder;
    else if (transform->position.y <= 0) transform->position.y = 0;*/
}

//void Player::Render(SDL_Renderer* renderer)
//{
    /*//render bullets first (so player is always on top)
    for (size_t i = 0; i < poolSize; i++)
    {
        if (bullets[i].isActive) bullets[i].Render(renderer);
    }

    //compute animation frame
    uint32_t animFrame = (SDL_GetTicks64() * animSpeed / 1000) % 2; //2 frames for this anim

    //source rectangle for the blit
    SDL_Rect src = {static_cast<int>(animFrame * 64), 0, 64, 64};

    //dest rectangle
    SDL_FRect dst = {pos.x, pos.y, dim.x, dim.y};

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyF(renderer, texture, &src, &dst);*/
//}

void Player::Ready()
{
    Logger::Log("Player ready.");
    
    Engine::GetInstance().sceneTree->AddComponent<TextureRect>(this, Engine::GetInstance().resourcesManager->GetTexture("Ship"));
}