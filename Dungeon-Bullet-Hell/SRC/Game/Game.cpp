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
#include "../Engine/Components/TileMap2D.h"
#include "GameObject/Enemy.h"

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

    //Gamepad mapping (assuming Xbox-style controller)
    inputManager->BindButton(Action::MoveLeft, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    inputManager->BindButton(Action::MoveRight, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    inputManager->BindButton(Action::MoveUp, SDL_CONTROLLER_BUTTON_DPAD_UP);
    inputManager->BindButton(Action::MoveDown, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    inputManager->BindButton(Action::Shoot, SDL_CONTROLLER_BUTTON_A);

    GenMap();
    
    //Create player
    player = sceneTree->AddGameObject<Player>("Player");
    player->GetComponent<Transform2D>().position = glm::vec2(DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT / 2.0f);

    /*glm::vec2 center = glm::vec2(DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT / 2.0f);
    float radius = 1000.0f;
    for (int i = 0; i < 10; i++)
    {
        float angle = static_cast<float>(i) * (2.0f * 3.14f) / 10.0f; // Angle en radians pour chaque point
        glm::vec2 position;
        position.x = center.x + radius * glm::cos(angle);
        position.y = center.y + radius * glm::sin(angle);

        Enemy* enemy = sceneTree->AddGameObject<Enemy>();
        enemy->GetComponent<Transform2D>().position = position;
    }*/
}


void Game::GenMap()
{
    RoomList roomList;
    DungeonGenerator generator;
    generator.GenerateDungeon(15); 
    generator.PrintDungeon();

    std::cout << "\nDétails des salles:\n";
    for (Room* room : generator.rooms) {
        std::cout << "Salle à (" << room->position.x << ", " << room->position.y << "), Portes: " << room->GetDoorCount();
        
        // Afficher les orientations des portes
        std::cout << " (";
        bool firstDoor = true;
        if (room->connections.at(Direction::NORTH)) {
            std::cout << "N";
            firstDoor = false;
        }
        if (room->connections.at(Direction::SOUTH)) {
            if (!firstDoor) std::cout << ", ";
            std::cout << "S";
            firstDoor = false;
        }
        if (room->connections.at(Direction::EAST)) {
            if (!firstDoor) std::cout << ", ";
            std::cout << "E";
            firstDoor = false;
        }
        if (room->connections.at(Direction::WEST)) {
            if (!firstDoor) std::cout << ", ";
            std::cout << "W";
        }
        std::cout << ")\n";

        const RoomResource* roomRes = roomList.GetBestRoomResource(room);

        if (roomRes != nullptr)
        {
            glm::ivec2 roomSize = {20, 20};
            float finalTileSize = 5;
            Empty* roomLevel = sceneTree->AddGameObject<Empty>();
            roomLevel->transform->position = room->position * finalTileSize * 20.0f;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Floor.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -2;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Walls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -1;
            roomLevel->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Maps/WallFloor.png"), std::string(roomRes->csvPath) + "_Overlay.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize).ZOrder = -1;
            roomLevel->AddComponent<ColliderTileMap2D>(std::string(roomRes->csvPath) + "_Colls.csv", roomSize.x, roomSize.y, finalTileSize, finalTileSize);

            Logger::Log("Room generated");
        }
    }
}