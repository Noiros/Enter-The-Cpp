#include "Game.h"
#include "../Engine/Logger.h"
#include "../Engine/Modules/RenderingServer.h"
#include <SDL.h>
#include "Nodes/Player.h"
#include "Nodes/Empty.h"
#include <glm.hpp>
#include "../Engine/Engine.h"
#include "../Engine/Components/TileMap.h"

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
    
    resourcesManager->AddTexture("Ship", "./Assets/Images/Ship.tga");
    resourcesManager->AddTexture("Bullet", "./Assets/Images/Bullet.tga");

    //Load tiles
    resourcesManager->AddTexture("TilesetFloor", "./Assets/Images/Tiles/TilesetFloor.tga");
    resourcesManager->AddTexture("TilesetHouse", "./Assets/Images/Tiles/TilesetHouse.tga");
    resourcesManager->AddTexture("TilesetNature", "./Assets/Images/Tiles/TilesetNature.tga");
    resourcesManager->AddTexture("TilesetProps", "./Assets/Images/Tiles/TilesetProps.tga");
    
    //Create level
    Empty* level = sceneTree->AddNode<Empty>();
    glm::ivec2 levelSize = {128, 128};
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesetFloor"), "./Assets/Maps/MainMap_Floor.csv", levelSize.x, levelSize.y)->ZOrder = -2;
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesetHouse"), "./Assets/Maps/MainMap_House.csv", levelSize.x, levelSize.y)->ZOrder = -1;
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesetProps"), "./Assets/Maps/MainMap_Props.csv", levelSize.x, levelSize.y)->ZOrder = -1;
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesetNature"), "./Assets/Maps/MainMap_Nature.csv", levelSize.x, levelSize.y)->ZOrder = -1;
    
    //Create player
    player = sceneTree->AddNode<Player>();
    player->transform->position.x = DISPLAY_WIDTH / 2.0f;
    player->transform->position.y = DISPLAY_HEIGHT / 2.0f;
}
