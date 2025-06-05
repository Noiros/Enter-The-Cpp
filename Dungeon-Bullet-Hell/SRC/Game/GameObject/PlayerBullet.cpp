#include "PlayerBullet.h"

#include "Enemy.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Components/Collider2D.h"


void PlayerBullet::Ready()
{
    SpriteSheet spriteSheet("./Assets/FXs/CanonBall.png", {16, 16});
    Animation animator({0, 1, 2, 3, 4}, spriteSheet, 0.1f);

    animatedSprite = &AddComponent<AnimatedSprite2D>(spriteSheet);
    animatedSprite->AddAnimation("Idle", animator);
    animatedSprite->PlayAnimation("Idle");
    
    transform->size = glm::vec2(16);
    
    movement = &AddComponent<CharacterMovement2D>();
    transform->rotation = glm::degrees(std::atan2(direction.y, direction.x));
    movement->SetLinearVelocity(direction * bulletSpeed * 1000.0f);

    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape).isTrigger = true;
}

void PlayerBullet::HitObject(GameObject* other)
{
    if (shooterObject != other)
    {
        GameObject::HitObject(other);
        
        auto* enemy = dynamic_cast<Enemy*>(other);
        if (enemy) {
            enemy->HP -= 1;
            if (enemy->HP <= 0) SceneTree::Get().DestroyGameObject(enemy);
        }
        SceneTree::Get().DestroyGameObject(this);
    }
}
