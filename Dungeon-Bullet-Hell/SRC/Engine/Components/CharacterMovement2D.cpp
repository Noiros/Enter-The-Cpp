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
    if (gameObject->HasComponent<Collider2D>())
    {
        if (PhysicsServer::Get().TestMovement(&gameObject->GetComponent<Collider2D>(), glm::vec2(velocity.x, 0) * deltaTime) == false)
        {
            transform->position.x += velocity.x * deltaTime;
        }
        if (PhysicsServer::Get().TestMovement(&gameObject->GetComponent<Collider2D>(), glm::vec2(0, velocity.y) * deltaTime) == false)
        {
            transform->position.y += velocity.y * deltaTime;
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
