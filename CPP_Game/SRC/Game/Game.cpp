#include "Game.h"
#include "../Engine/Logger.h"
#include "../Engine/Modules/RenderingServer.h"
#include <SDL.h>
#include "Nodes/Player.h"
#include "Nodes/Empty.h"
#include <glm.hpp>
#include "../Engine/Engine.h"
#include "../Engine/Components/TileMap2D.h"
#include "Nodes/Enemy.h"

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
    InputManager* inputManager = &InputManager::GetInstance();
    ResourcesManager* resourcesManager = &ResourcesManager::GetInstance();
    SceneTree* sceneTree = &SceneTree::GetInstance();

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
    Empty* level = sceneTree->AddNode<Empty>();
    glm::ivec2 levelSize = {128, 128};
    float finalTileSize = 64;
    sceneTree->AddComponent<TileMap2D>(level, resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetFloor.tga"), "./Assets/Maps/MainMap_Floor.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize)->ZOrder = -2;
    sceneTree->AddComponent<TileMap2D>(level, resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetHouse.tga"), "./Assets/Maps/MainMap_House.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize)->ZOrder = -1;
    sceneTree->AddComponent<TileMap2D>(level, resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetProps.tga"), "./Assets/Maps/MainMap_Props.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize)->ZOrder = -1;
    sceneTree->AddComponent<TileMap2D>(level, resourcesManager->GetTexture("./Assets/Images/Tiles/TilesetNature.tga"), "./Assets/Maps/MainMap_Nature.csv", levelSize.x, levelSize.y, finalTileSize, finalTileSize)->ZOrder = -1;
    
    //Create player
    player = sceneTree->AddNode<Player>();
    player->transform->position.x = DISPLAY_WIDTH / 2.0f;
    player->transform->position.y = DISPLAY_HEIGHT / 2.0f;
    
    sceneTree->AddNode<Enemy>();
}
