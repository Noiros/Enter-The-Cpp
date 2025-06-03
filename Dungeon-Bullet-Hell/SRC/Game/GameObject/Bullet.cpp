#include "Bullet.h"

#include "../../Engine/Components/Sprite2D.h"


void Bullet::Ready()
{
    AddComponent<Sprite2D>(Sprite("./Assets/Images/FX/PlantSpike.png"));
    
    movement = &AddComponent<CharacterMovement2D>();

    transform->rotation = glm::degrees(std::atan2(direction.y, direction.x));
    movement->SetLinearVelocity(direction * bulletSpeed * 1000.0f);
}
