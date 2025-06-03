#include "PhysicsServer.h"

#include "../GameObject.h"

PhysicsServer* PhysicsServer::s_instance = nullptr;

void PhysicsServer::AddCollider(Collider2D* collider, int layer)
{
    colliders[layer].push_back(collider);
}

bool PhysicsServer::TestMovement(Collider2D* collider, glm::vec2 movement)
{
    SDL_Rect destAABB = collider->collisionShape.collisionShape;
    destAABB.x += movement.x + collider->gameObject->transform->position.x;
    destAABB.y += movement.y + collider->gameObject->transform->position.y;
    for (Collider2D* coll : colliders[collider->layer])
    {
        if (coll != collider && IsCollidingAABB(destAABB, coll->collisionShape.collisionShape) == true)
        {
            return true;
        }
    }
    return false;
}

bool PhysicsServer::IsColliding(Collider2D* obj1, Collider2D* obj2)
{
    return true;
}

bool PhysicsServer::IsCollidingAABB(SDL_Rect obj1, SDL_Rect obj2)
{
    if (obj1.x < obj2.x + obj2.w &&
        obj1.x + obj1.w > obj2.x &&
        obj1.y < obj2.y + obj2.h &&
        obj1.y + obj1.h > obj2.y)
    {
        return true;
    }
    return false;
}
