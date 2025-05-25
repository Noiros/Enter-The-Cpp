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
    
    resourcesManager->AddTexture("TilesField", "./Assets/Images/Tiles/Fields.tga");
    resourcesManager->AddTexture("TilesFences", "./Assets/Images/Tiles/Fences.tga");
    
    //Create level
    Empty* level = sceneTree->AddNode<Empty>();
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesField"), "./Assets/Maps/Main_Tiles.csv", 50, 50)->ZOrder = -2;
    sceneTree->AddComponent<TileMap>(level, resourcesManager->GetTexture("TilesFences"), "./Assets/Maps/Main_Objects.csv", 50, 50)->ZOrder = -1;
    
    //Create player
    player = sceneTree->AddNode<Player>();
    player->transform->position.x = DISPLAY_WIDTH / 2.0f;
    player->transform->position.y = DISPLAY_HEIGHT / 2.0f;
    
}
