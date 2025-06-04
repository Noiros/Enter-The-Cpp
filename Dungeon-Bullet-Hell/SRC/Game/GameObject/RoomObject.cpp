#include "RoomObject.h"

#include <Windows.h>

#include "Enemy.h"
#include "Player.h"
#include "../../Engine/Logger.h"
#include "../../Engine/Modules/PhysicsServer.h"
#include "../../Engine/Modules/SceneTree.h"

void RoomObject::Ready()
{
    CollisionShape area = CollisionShape({int(48*2), int(48*2), 48*16, 48*16});
    triggerArea = &AddComponent<Collider2D>(area);
    triggerArea->isTrigger = true;
}

void RoomObject::Update(float deltaTime)
{
    GameObject::Update(deltaTime);
    std::vector<Collider2D*> bodies = PhysicsServer::Get().GetOverloppingBodies(triggerArea, 0);

    bool isPlayerInRoom = false;
    bool isEnemiesStillAlive = false;
    
    for (Collider2D* body : bodies)
    {
        auto* player = dynamic_cast<Player*>(body->gameObject);
        if (player) isPlayerInRoom = true;
        
        auto* enemy = dynamic_cast<Enemy*>(body->gameObject);
        if (enemy) isEnemiesStillAlive = true;
    }

    if (isRoomActive == false && isPlayerInRoom == true && isEnemiesStillAlive == true)
    {
        isRoomActive = true;
        Activate();
    }
    else if (isRoomActive == true && isPlayerInRoom == true && isEnemiesStillAlive == false)
    {
        isRoomActive = false;
        Deactivate();
    } 
}

void RoomObject::Activate()
{
    Logger::Log("Room activated");

    std::vector<Collider2D*> bodies = PhysicsServer::Get().GetOverloppingBodies(triggerArea, 0);
    
    for (Collider2D* body : bodies)
    {
        auto* enemy = dynamic_cast<Enemy*>(body->gameObject);
        if (enemy) enemy->roomActive = true;
    }

    glm::ivec2 roomSize = {20, 20};
    float finalTileSize = 48;
    door = SceneTree::Get().AddGameObject<Empty>();
    door->AddComponent<TileMap2D>(ResourcesManager::Get().GetTexture("./Assets/Maps/WallFloor.png"), "./Assets/Maps/Room_Door_Walls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -3;
    door->AddComponent<ColliderTileMap2D>("./Assets/Maps/Room_Door_Colls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize);
    door->transform->position = transform->position;
}

void RoomObject::Deactivate()
{
    Logger::Log("Room deactivated");

    std::vector<Collider2D*> bodies = PhysicsServer::Get().GetOverloppingBodies(triggerArea, 0);
    
    for (Collider2D* body : bodies)
    {
        auto* enemy = dynamic_cast<Enemy*>(body->gameObject);
        if (enemy) enemy->roomActive = false;
    }

    SceneTree::Get().DestroyGameObject(door);
}
