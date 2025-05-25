#include "Game.h"
#include <iostream>
#include "../Engine/Logger.h"
#include "../Engine/Modules/RenderingServer.h"
#include <SDL.h>
#include "Player.h"
#include "../Engine/Utils.hpp"
#include <Windows.h>
#include <glm.hpp>
#include "../Engine/Engine.h"
#include "Level.h"

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
    inputManager->BindKey(Action::MoveLeft, SDL_SCANCODE_LEFT);
    inputManager->BindKey(Action::MoveRight, SDL_SCANCODE_RIGHT);
    inputManager->BindKey(Action::MoveUp, SDL_SCANCODE_UP);
    inputManager->BindKey(Action::MoveDown, SDL_SCANCODE_DOWN);
    inputManager->BindKey(Action::Shoot, SDL_SCANCODE_SPACE);

    //Gamepad mapping (assuming Xbox-style controller)
    inputManager->BindButton(Action::MoveLeft, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
    inputManager->BindButton(Action::MoveRight, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
    inputManager->BindButton(Action::MoveUp, SDL_CONTROLLER_BUTTON_DPAD_UP);
    inputManager->BindButton(Action::MoveDown, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
    inputManager->BindButton(Action::Shoot, SDL_CONTROLLER_BUTTON_A);

    resourcesManager->AddTexture("Ship", "./Assets/Images/Ship.tga");
    resourcesManager->AddTexture("Bullet", "./Assets/Images/Bullet.tga");
    resourcesManager->AddTexture("Tileset", "./Assets/Images/Tileset.tga");

    //Create level
    level = std::make_unique<Level>(resourcesManager->GetTexture("Tileset"), "./Assets/Maps/Level01.csv", 8, 64);

    sceneTree->AddNode<Player>();
}
