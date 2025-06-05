#pragma once
#include "../Components/Collider2D.h"
#include <map>
#include <vector>

class PhysicsServer
{
public:    
    PhysicsServer() {}
    ~PhysicsServer() {}
    
    void AddCollider(Collider2D* collider, int layer = 0);
    void RmCollider(Collider2D* collider);
    
    Collider2D* TestMovement(Collider2D* collider, glm::vec2 velocity);
    std::vector<Collider2D*> GetOverloppingBodies(Collider2D* collider, int layer);
    bool IsColliding(Collider2D* obj1, Collider2D* obj2);
    bool IsCollidingAABB(SDL_Rect obj1, SDL_Rect obj2);

    static void SetInstance(PhysicsServer* instance) { s_instance = instance; }
    static PhysicsServer& Get() { return *s_instance; }
    PhysicsServer(const PhysicsServer&) = delete;
    PhysicsServer& operator=(const PhysicsServer&) = delete;

    
private:
    static PhysicsServer* s_instance;
    std::map<int, std::vector<Collider2D*>> colliders;
};
