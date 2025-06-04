#include "Bullet.h"

#include "Enemy.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Components/Sprite2D.h"
#include "../../Engine/Components/Collider2D.h"


void Bullet::Ready()
{
    AddComponent<Sprite2D>(Sprite("./Assets/Images/FX/PlantSpike.png"));
    transform->size = glm::vec2(20);
    
    movement = &AddComponent<CharacterMovement2D>();

    transform->rotation = glm::degrees(std::atan2(direction.y, direction.x));
    movement->SetLinearVelocity(direction * bulletSpeed * 1000.0f);

    CollisionShape collisionShape({-16, -16, 32, 32});
    AddComponent<Collider2D>(collisionShape).isTrigger = true;
}

void Bullet::HitObject(GameObject* other)
{
    if (shooterObject != other)
    {
        GameObject::HitObject(other);
        
        auto* enemy = dynamic_cast<Enemy*>(other);
        if (enemy) {
            Logger::Log("test");
            SceneTree::Get().DestroyGameObject(enemy);
        }
        SceneTree::Get().DestroyGameObject(this);
    }
}
