#include "Enemy.h"

#include "../../Engine/Modules/SceneTree.h"

void Enemy::Ready()
{
    SpriteSheet spriteSheet("./Assets/Images/Characters/Skeleton.png", {16, 16});
    
    AnimatedSprite2D* animatedSprite = SceneTree::GetInstance().AddComponent<AnimatedSprite2D>(this, spriteSheet);
    
    Animation animIdle({0}, spriteSheet, 1.0f);
    animatedSprite->AddAnimation("Idle", animIdle);
    Animation animWalkUp({9, 13, 17, 21}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkUp", animWalkUp);

    animatedSprite->PlayAnimation("Idle");
}
