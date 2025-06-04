#include "PhysicsServer.h"

#include "../GameObject.h"

PhysicsServer* PhysicsServer::s_instance = nullptr;

void PhysicsServer::AddCollider(Collider2D* collider, int layer)
{
    colliders[layer].push_back(collider);
}

void PhysicsServer::RmCollider(Collider2D* collider)
{
    for (auto it = colliders.begin(); it != colliders.end(); ++it)
    {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if (*it2 == collider)
            {
                it->second.erase(it2);
                return;
            }
        }
    }
}

Collider2D* PhysicsServer::TestMovement(Collider2D* collider, glm::vec2 movement)
{
    SDL_Rect destAABB = collider->collisionShape.collisionShape;
    destAABB.x += movement.x + collider->gameObject->transform->position.x;
    destAABB.y += movement.y + collider->gameObject->transform->position.y;
    for (Collider2D* coll : colliders[collider->layer])
    {
        SDL_Rect testAABB = coll->collisionShape.collisionShape;
        testAABB.x += coll->gameObject->transform->position.x;
        testAABB.y += coll->gameObject->transform->position.y;
        if (coll->gameObject->IsActive() && coll->isTrigger == false && coll != collider && IsCollidingAABB(destAABB, testAABB) == true)
        {
            return coll;
        }
    }
    return nullptr;
}

Collider2D* PhysicsServer::IsOverlapping(Collider2D* collider)
{
    SDL_Rect destAABB = collider->collisionShape.collisionShape;
    destAABB.x += collider->gameObject->transform->position.x;
    destAABB.y += collider->gameObject->transform->position.y;
    for (Collider2D* coll : colliders[collider->layer])
    {
        SDL_Rect testAABB = coll->collisionShape.collisionShape;
        testAABB.x += coll->gameObject->transform->position.x;
        testAABB.y += coll->gameObject->transform->position.y;
        if (coll != collider && IsCollidingAABB(destAABB, testAABB) == true)
        {
            return coll;
        }
    }
    return nullptr;
}

std::vector<Collider2D*> PhysicsServer::GetOverloppingBodies(Collider2D* collider, int layer)
{
    std::vector<Collider2D*> bodies;
    
    SDL_Rect destAABB = collider->collisionShape.collisionShape;
    destAABB.x += collider->gameObject->transform->position.x;
    destAABB.y += collider->gameObject->transform->position.y;
    
    for (Collider2D* coll : colliders[collider->layer])
    {
        SDL_Rect testAABB = coll->collisionShape.collisionShape;
        testAABB.x += coll->gameObject->transform->position.x;
        testAABB.y += coll->gameObject->transform->position.y;
        if (coll->gameObject->IsActive() && coll != collider && IsCollidingAABB(destAABB, testAABB) == true)
        {
            bodies.push_back(coll);
        }
    }
    
    return bodies;
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
