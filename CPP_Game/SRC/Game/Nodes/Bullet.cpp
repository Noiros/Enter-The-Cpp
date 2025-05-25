#include "../Game.h"
#include "Bullet.h"
#include "../../Engine/Components/Sprite2D.h"

void Bullet::Ready()
{
    SpriteSheet sheet("./Assets/Images/FX/PlantSpike.png", {16, 16});
    Animation animIdle({0, 1, 2, 3}, sheet, 0.1f);
    AnimatedSprite2D* sprite = SceneTree::GetInstance().AddComponent<AnimatedSprite2D>(this, sheet);
    movement = SceneTree::GetInstance().AddComponent<CharacterMovement2D>(this);

    sprite->AddAnimation("Idle", animIdle);
    sprite->PlayAnimation("Idle");
}

void Bullet::Update(float deltaTime)
{
    
}




/*
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
}*/
