#include "BaseEnemy.h"

void BaseEnemy::Ready()
{
    SpriteSheet spriteSheet("./Assets/Characters/BaseEnemy.png", {16, 16});
    
    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    
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
    Animation animDash({0, 1, 2, 3}, spriteSheet, 0.1f);
    
    Enemy::Ready();
}
