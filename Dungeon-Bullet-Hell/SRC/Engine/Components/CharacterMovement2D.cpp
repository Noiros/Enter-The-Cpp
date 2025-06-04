#include "CharacterMovement2D.h"

#include <SDL_timer.h>

#include "../Modules/PhysicsServer.h""
#include "Collider2D.h"
#include "../GameObject.h"
#include "../Modules/SceneTree.h"
#include "../GameObject.h"

float timer = 0.0f;
float delay = 5000.0f;

void CharacterMovement2D::Update(float deltaTime)
{
    if (transform == nullptr) return;
    
    if (gameObject->HasComponent<Collider2D>())
    {
        if (gameObject->GetComponent<Collider2D>().isTrigger)
        {
            Collider2D* collider = PhysicsServer::Get().TestMovement(&gameObject->GetComponent<Collider2D>(), velocity * deltaTime);
            if (collider != nullptr) gameObject->HitObject(collider->gameObject);
            transform->position += velocity * deltaTime;
        }
        else
        {
            Collider2D* collider;
            collider = PhysicsServer::Get().TestMovement(&gameObject->GetComponent<Collider2D>(), glm::vec2(velocity.x, 0) * deltaTime);
            if (collider == nullptr)
            {
                transform->position.x += velocity.x * deltaTime;
            }
            else
            {
                gameObject->HitObject(collider->gameObject);
            }
            collider = PhysicsServer::Get().TestMovement(&gameObject->GetComponent<Collider2D>(), glm::vec2(0, velocity.y) * deltaTime);
            if (collider == nullptr)
            {
                transform->position.y += velocity.y * deltaTime;
            }
            else
            {
                gameObject->HitObject(collider->gameObject);
            }
        }
    } else
    {
        transform->position += velocity * deltaTime;
    }
}

void CharacterMovement2D::Ready()
{
    transform = &gameObject->GetComponent<Transform2D>();
}
