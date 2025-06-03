#include "Game.h"
#include "../Engine/Logger.h"
#include "../Engine/Modules/RenderingServer.h"
#include <SDL.h>
#include "GameObject/Player.h"
#include "GameObject/Empty.h"
#include <glm.hpp>
#include "../Engine/Engine.h"
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
    InputManager* inputManager = &InputManager::Get();
    ResourcesManager* resourcesManager = &ResourcesManager::Get();
    SceneTree* sceneTree = &SceneTree::Get();

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

    //Create level
    glm::ivec2 levelSize = {128, 128};
    float finalTileSize = 64;
    
    Empty* level = sceneTree->AddGameObject<Empty>();
    level->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetFloor.tga"), "./Assets/Maps/MainMap_Floor.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize).ZOrder = -2;
    level->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetHouse.tga"), "./Assets/Maps/MainMap_House.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize).ZOrder = -1;
    level->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetProps.tga"), "./Assets/Maps/MainMap_Props.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize).ZOrder = -1;
    level->AddComponent<TileMap2D>(resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetNature.tga"), "./Assets/Maps/MainMap_Nature.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize).ZOrder = -1;
    
    //Create player
    player = sceneTree->AddGameObject<Player>("Player");
    player->GetComponent<Transform2D>().position = glm::vec2(DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT / 2.0f);

    /*glm::vec2 center = glm::vec2(DISPLAY_WIDTH / 2.0f, DISPLAY_HEIGHT / 2.0f);
    float radius = 1000.0f;
    for (int i = 0; i < 10; i++)
    {
        float angle = static_cast<float>(i) * (2.0f * 3.14) / 10.0f; // Angle en radians pour chaque point
        glm::vec2 position;
        position.x = center.x + radius * glm::cos(angle);
        position.y = center.y + radius * glm::sin(angle);

        Enemy* enemy = sceneTree->AddGameObject<Enemy>();
        enemy->GetComponent<Transform2D>().position = position;
    }*/
}
