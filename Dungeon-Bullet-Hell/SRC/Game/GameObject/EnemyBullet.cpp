#include "EnemyBullet.h"

#include "Enemy.h"
#include "../../Engine/Components/Collider2D.h"


void EnemyBullet::Ready()
{
    SpriteSheet spriteSheet("./Assets/FXs/Fireball.png", {16, 16});
    Animation animator({0, 1, 2, 3}, spriteSheet, 0.1f);

    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    animatedSprite->AddAnimation("Idle", animator);
    animatedSprite->PlayAnimation("Idle");
    
    transform->size = glm::vec2(32);
    
    movement = &AddComponent<CharacterMovement2D>();

    transform->rotation = glm::degrees(std::atan2(direction.y, direction.x));
    movement->SetLinearVelocity(direction * bulletSpeed * 300.0f);

    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape).isTrigger = true;
}

void EnemyBullet::HitObject(GameObject* other)
{
    if (shooterObject != other)
    {
        GameObject::HitObject(other);
        
        auto* player = dynamic_cast<Player*>(other);
        if (player) {
            player->TakeDamage(1);
        }
        auto* enemy = dynamic_cast<Enemy*>(other);
        if (!enemy)
        {
            SceneTree::Get().DestroyGameObject(this);
        }
    }
}
