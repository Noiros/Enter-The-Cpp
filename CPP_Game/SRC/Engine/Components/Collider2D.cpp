#include "Collider2D.h"
#include "../GameObject.h"

void Collider2D::Ready()
{
    transform = &gameObject->GetComponent<Transform2D>();
}

void Collider2D::Update(float deltaTime)
{
    Component2D::Update(deltaTime);
}

void Collider2D::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    SDL_Rect dst = {int(transform->position.x) + collisionShape.collisionShape.x - int(cameraPos.x), int(transform->position.y) + collisionShape.collisionShape.y - int(cameraPos.y), int(collisionShape.collisionShape.w * cameraScale), int(collisionShape.collisionShape.h * cameraScale)};
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawRect(renderer, &dst);
}
