#include "Gun.h"

#include "Bullet.h"
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
    
    lookAtDir = glm::normalize(glm::vec2(InputManager::Get().GetMouseX() - (DISPLAY_WIDTH / 2.0f), InputManager::Get().GetMouseY() - (DISPLAY_HEIGHT / 2.0f)));
    
    transform->position = parent->transform->position;
    transform->rotation = glm::degrees(std::atan2(lookAtDir.y, lookAtDir.x));

    if (InputManager::Get().IsActionHeld(Action::Shoot) && SDL_GetTicks() - lastFire >= fireRate * 1000.0f) {
        Shoot();
    }
}

void Gun::Shoot()
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<> dis(-0.1, 0.1); 
    float spreadAngle = dis(gen);
    
    glm::vec2 spreadFireDir;
    float cosSpread = std::cos(spreadAngle);
    float sinSpread = std::sin(spreadAngle);
    spreadFireDir.x = lookAtDir.x * cosSpread - lookAtDir.y * sinSpread;
    spreadFireDir.y = lookAtDir.x * sinSpread + lookAtDir.y * cosSpread;
    
    lastFire = SDL_GetTicks();
    Bullet* bullet = SceneTree::Get().AddGameObject<Bullet>("", spreadFireDir, parent);
    bullet->transform->position = transform->position;
    bullet->bulletSpeed = bulletSpeed;
}