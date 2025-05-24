#include "Game.h"
#include "Player.h"
#include "../Engine/Utils.hpp"
#include <iostream>

bool Bullet::Update(float deltaTime)
{
    const float rightBorder = DISPLAY_WIDTH - dim.x;
    const float bottomBorder = DISPLAY_HEIGHT - dim.y;

    state.params.pos += state.params.vel * deltaTime;

    if (state.params.pos.x >= rightBorder)
    {
        //state.params.pos.x = rightBorder - (state.params.pos.x - rightBorder);
        //state.params.vel.x = -state.params.vel.x;
        return true; //e.g. a collision with an enemy occurs
    }
    if (state.params.pos.x <= 0)
    {
        //state.params.pos.x = -state.params.pos.x;
        //state.params.vel.x = -state.params.vel.x;
        return true;
    }

    if (state.params.pos.y >= bottomBorder)
    {
        state.params.pos.y = bottomBorder - (state.params.pos.y - bottomBorder);
        state.params.vel.y = -state.params.vel.y;
    }
    else if (state.params.pos.y <= 0)
    {
        state.params.pos.y = -state.params.pos.y;
        state.params.vel.y = -state.params.vel.y;
    }
    return false;
}

void Bullet::Render(SDL_Renderer* renderer)
{
    //source rectangle for the blit
    static constexpr SDL_Rect src = {0, 0, 8, 8};

    //dest rectangle
    SDL_FRect dst = {state.params.pos.x, state.params.pos.y, dim.x, dim.y};

    //blit
    SDL_SetTextureColorMod(texture, color.r, color.g, color.b);
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_RenderCopyF(renderer, texture, &src, &dst);
}

void Player::Shoot(vec2 pos, vec2 vel)
{
    if (head)
    {
        Bullet* bullet = head;
        head = bullet->state.next;

        bullet->state.params.pos = pos;
        bullet->state.params.vel = vel;
        bullet->isActive = true;
    }
}

void Player::Update(float deltaTime)
{
    if (input->IsActionHeld(Action::MoveLeft)) pos.x -= speed * deltaTime;
    if (input->IsActionHeld(Action::MoveRight)) pos.x += speed * deltaTime;
    if (input->IsActionHeld(Action::MoveUp)) pos.y -= speed * deltaTime;
    if (input->IsActionHeld(Action::MoveDown)) pos.y += speed * deltaTime;
    if (input->IsActionHeld(Action::Shoot)) Shoot(vec2(pos + vec2(28, 0)), vec2(0, -500) + Utils::RndVec2(-50, 50));

    pos.x += input->GetLeftStickX() * speed * deltaTime;
    pos.y += input->GetLeftStickY() * speed * deltaTime;

    //clamp position to borders
    const float rightBorder = DISPLAY_WIDTH - dim.x;
    const float bottomBorder = DISPLAY_HEIGHT - dim.y;

    if (pos.x >= rightBorder) pos.x = rightBorder;
    else if (pos.x <= 0) pos.x = 0;
    if (pos.y >= bottomBorder) pos.y = bottomBorder;
    else if (pos.y <= 0) pos.y = 0;

    //bullets update
    for (size_t i = 0; i < poolSize; i++)
    {
        if (bullets[i].isActive)
        {
            if (bullets[i].Update(deltaTime))
            {
                bullets[i].isActive = false;
                bullets[i].state.next = head;
                head = &bullets[i];
            }
        }
    }

#ifndef NDEBUG
    //std::cout << "Num of bullets: " << bullets.size() << std::endl;
#endif
}

void Player::Render(SDL_Renderer* renderer)
{
    //render bullets first (so player is always on top)
    for (size_t i = 0; i < poolSize; i++)
    {
        if (bullets[i].isActive) bullets[i].Render(renderer);
    }

    //compute animation frame
    uint32_t animFrame = (SDL_GetTicks64() * animSpeed / 1000) % 2; //2 frames for this anim

    //source rectangle for the blit
    SDL_Rect src = {animFrame * 64, 0, 64, 64};

    //dest rectangle
    SDL_FRect dst = {pos.x, pos.y, dim.x, dim.y};

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyF(renderer, texture, &src, &dst);
}
