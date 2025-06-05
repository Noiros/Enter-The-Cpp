#include "Gun.h"

#include "EnemyBullet.h"
#include "PlayerBullet.h"
#include "../Game.h"
#include "../../Engine/Modules/InputManager.h"

void Gun::Ready()
{
    GameObject::Ready();

    sprite = &AddComponent<Sprite2D>(Sprite("./Assets/Guns/milit.png"));
    transform->scale = glm::vec2(3.0f);
    transform->anchor = glm::vec2(-0.5f, 0.5f);
}

void Gun::Update(float deltaTime)
{
    GameObject::Update(deltaTime);

    glm::vec2 velocity = parent->GetComponent<CharacterMovement2D>().GetLinearVelocity();
    if (velocity == glm::vec2(0, 0))
    {
        transform->position = parent->transform->position;
    }
    else
    {
        transform->position = parent->transform->position + glm::normalize(velocity) * 20.0f;
    }
    
    transform->rotation = glm::degrees(std::atan2(lookAtDir.y, lookAtDir.x));
    sprite->VFlip = lookAtDir.x < 0.0f;

    if (team == PLAYER)
    {
        InputManager* inputManager = &InputManager::Get();
        if (inputManager->GetRightStickX() != 0.0f || inputManager->GetRightStickY() != 0.0f)
        {
            lookAtDir = glm::vec2(inputManager->GetRightStickX(), inputManager->GetRightStickY());
        } else lookAtDir = glm::normalize(glm::vec2(inputManager->GetMouseX() - (DISPLAY_WIDTH / 2.0f), inputManager->GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));
        if (InputManager::Get().IsActionHeld(Action::Shoot)) {
            Shoot();
        }
    }
}

void Gun::Shoot()
{
    if (SDL_GetTicks() - lastFire < fireRate * 1000) return;

    lastFire = SDL_GetTicks();
    
    float totalSpreadAngle = glm::radians(gunSpread);
    float angleStep = 0.0f;
    float startAngle = 0;
    if (bulletsPerShot > 1) {
        angleStep = totalSpreadAngle / (bulletsPerShot - 1);
        startAngle = -totalSpreadAngle / 2.0f;
    }
    float randomSpreadAngle = (static_cast<float>(rand()) / RAND_MAX - 0.5f) * totalSpreadAngle;
    
    for (int i = 0; i < bulletsPerShot; ++i)
    {
        float currentAngle = startAngle + i * angleStep + randomSpreadAngle;
        
        glm::vec2 fireDir = glm::normalize(lookAtDir);
        
        glm::vec2 spreadFireDir;
        spreadFireDir.x = fireDir.x * std::cos(currentAngle) - fireDir.y * std::sin(currentAngle);
        spreadFireDir.y = fireDir.x * std::sin(currentAngle) + fireDir.y * std::cos(currentAngle);
        
        if (team == PLAYER)
        {
            PlayerBullet* bullet = SceneTree::Get().AddGameObject<PlayerBullet>("", spreadFireDir, parent);
            bullet->transform->position = transform->position;
            bullet->bulletSpeed = bulletSpeed;
        }
        if (team == ENEMY)
        {
            EnemyBullet* bullet = SceneTree::Get().AddGameObject<EnemyBullet>("", spreadFireDir, parent);
            bullet->transform->position = transform->position;
            bullet->bulletSpeed = bulletSpeed;
        }
    }
}
