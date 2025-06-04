#include "Enemy.h"

#include "../../Engine/Modules/SceneTree.h"
#include "../../Engine/Components/AnimatedSprite2D.h"

void Enemy::Ready()
{
    SpriteSheet spriteSheet("./Assets/Images/Characters/Skeleton.png", {16, 16});
    
    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    
    Animation animIdle({0}, spriteSheet, 1.0f);
    animatedSprite->AddAnimation("Idle", animIdle);
    Animation animWalkUp({9, 13, 17, 21}, spriteSheet, 0.1f);
    animatedSprite->AddAnimation("WalkUp", animWalkUp);

    animatedSprite->PlayAnimation("Idle");

    movement = &AddComponent<CharacterMovement2D>();
    transform = &GetComponent<Transform2D>();

    player = &SceneTree::Get().GetGameObjectByName<Player>("Player");
    
    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape);
}

void Enemy::Update(float deltaTime)
{
    //glm::vec2 moveDirection = glm::normalize(player->GetComponent<Transform2D>().position - transform->position);
    //movement->SetLinearVelocity( moveDirection * 200.0f );
}
