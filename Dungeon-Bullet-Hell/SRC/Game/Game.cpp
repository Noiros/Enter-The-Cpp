#include "Game.h"
#include "../Engine/Logger.h"
#include "../Engine/Modules/RenderingServer.h"
#include <SDL.h>
#include "GameObject/Player.h"
#include "GameObject/Empty.h"
#include <glm.hpp>

#include "RoomList.h"
#include "../Engine/Plugins/DungeonGenerator.h"
#include "../Engine/Engine.h"
#include "../Engine/Components/ColliderTileMap2D.h"
#include "../Engine/Components/ObjectTileMap2D.h"
#include "../Engine/Components/TileMap2D.h"
#include "GameObject/Enemy.h"
#include "GameObject/RoomObject.h"
#include "GameObject/Enemies/BaseEnemy.h"
#include "GameObject/Enemies/ShotgunEnemy.h"

Game::Game()
{
    Logger::Log("Game constructor called");
}

Game::~Game()
{
    Logger::Log("Game destructor called");
}

void Game::Start(Engine* engine)
{
    inputManager = &InputManager::Get();
    resourcesManager = &ResourcesManager::Get();
    sceneTree = &SceneTree::Get();

    //Game setup
    //Keyboard bindings
    inputManager->BindKey(Action::MoveLeft, SDL_SCANCODE_A);
    inputManager->BindKey(Action::MoveRight, SDL_SCANCODE_D);
    inputManager->BindKey(Action::MoveUp, SDL_SCANCODE_W);
    inputManager->BindKey(Action::MoveDown, SDL_SCANCODE_S);
    inputManager->BindKey(Action::Shoot, SDL_SCANCODE_SPACE);
    inputManager->BindKey(Action::Dash, SDL_SCANCODE_LSHIFT);

    //Gamepad mapping (assuming Xbox-style controller)
    inputManager->BindButton(Action::MoveLeft, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    inputManager->BindButton(Action::MoveRight, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    inputManager->BindButton(Action::MoveUp, SDL_CONTROLLER_BUTTON_DPAD_UP);
    inputManager->BindButton(Action::MoveDown, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    inputManager->BindButton(Action::Shoot, SDL_CONTROLLER_BUTTON_RIGHTSHOULDER);
    inputManager->BindButton(Action::Dash, SDL_CONTROLLER_BUTTON_LEFTSHOULDER);

    //Create player
    player = sceneTree->AddGameObject<Player>("Player");
    player->transform->position = glm::vec2(10, 10) * 48.0f;
        
    //Initialize gameObjects IDs
    sceneTree->RegisterGameObjectFactory(0, [](std::string_view name){ return std::make_unique<BaseEnemy>(); });
    sceneTree->RegisterGameObjectFactory(1, [](std::string_view name){ return std::make_unique<ShotgunEnemy>(); });

    GenMap();
}


void Game::GenMap()
{
    RoomList roomList;
    DungeonGenerator generator;
    generator.GenerateDungeon(50); // Gen a map of 50 rooms
    
    for (Room* room : generator.rooms) {
        Logger::Log("Add Room (" + std::to_string(room->position.x) + ", " + std::to_string(room->position.y) + ") Door count: " + std::to_string(room->GetDoorCount()));
        
        const RoomResource* roomRes = roomList.GetBestRoomResource(room);

        // Generate the room
        if (roomRes != nullptr)
        {
            glm::ivec2 roomSize = {20, 20};
            float finalTileSize = 48;
            RoomObject* roomLevel = sceneTree->AddGameObject<RoomObject>();
            roomLevel->transform->position = glm::vec2(room->position.x, -room->position.y) * finalTileSize * 20.0f;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Floor.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -4;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Walls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -2;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Overlay.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -2;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/Deco.png"), std::string(roomRes->csvPath) + "_Deco.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -1;
            roomLevel->AddComponent<ColliderTileMap2D>(std::string(roomRes->csvPath) + "_Colls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize);
            roomLevel->AddComponent<ObjectTileMap2D>(std::string(roomRes->csvPath) + "_Objects.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize);

            Logger::Log("Room generated");
        }
    }
}