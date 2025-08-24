#include "Enemy.h"

#include "../../Engine/Modules/SceneTree.h"
#include "../../Engine/Components/AnimatedSprite2D.h"

void Enemy::Ready()
{
    animatedSprite->PlayAnimation("Idle");
    movement = &AddComponent<CharacterMovement2D>();
    transform = &GetComponent<Transform2D>();

    player = &SceneTree::Get().GetGameObjectByName<Player>("Player");
    
    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape);
    EquipGun();
}

void Enemy::EquipGun()
{
    gun = SceneTree::Get().AddGameObject<Gun>("", this);
    gun->team = ENEMY;
    gun->fireRate = 1.5f;
}

void Enemy::Update(float deltaTime)
{
    if (!roomActive) return;
    
    movement->SetLinearVelocity(glm::vec2(0, 0));
    
    float playerDistance = glm::distance(player->GetComponent<Transform2D>().position, transform->position);

    if (playerDistance < viewDistance)
    {
        gun->lookAtDir = glm::normalize(player->GetComponent<Transform2D>().position - transform->position);
        gun->Shoot();
        if (playerDistance > attackDistance)
        {
            glm::vec2 moveDirection = glm::normalize(player->GetComponent<Transform2D>().position - transform->position);
            movement->SetLinearVelocity( moveDirection * 200.0f );
        }
    }

    if (movement->GetLinearVelocity() == glm::vec2(0, 0)) animatedSprite->PlayAnimation("Idle");
    if (movement->GetLinearVelocity().x < 0) animatedSprite->PlayAnimation("WalkLeft");
    if (movement->GetLinearVelocity().x > 0) animatedSprite->PlayAnimation("WalkRight");
    if (movement->GetLinearVelocity().y < 0) animatedSprite->PlayAnimation("WalkUp");
    if (movement->GetLinearVelocity().y > 0) animatedSprite->PlayAnimation("WalkDown");
}

void Enemy::TakeDamage(int damage)
{
    
}