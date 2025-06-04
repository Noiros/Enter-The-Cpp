#include "EnemyBullet.h"

#include "Enemy.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Components/Sprite2D.h"
#include "../../Engine/Components/Collider2D.h"


void EnemyBullet::Ready()
{    
    AddComponent<Sprite2D>(Sprite("./Assets/FXs/Fireball.png"));
    transform->size = glm::vec2(20);
    
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
        if (player && !player->isDashing) {
            player->HP -= 1;
            if (player->HP <= 0) SceneTree::Get().DestroyGameObject(player);
        }
        SceneTree::Get().DestroyGameObject(this);
    }
}
