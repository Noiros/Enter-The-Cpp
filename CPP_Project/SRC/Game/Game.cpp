#include "Game.h"
#include <iostream>
#include "../Engine/Logger.h"
#include <SDL.h>
#include "Player.h"
#include "../Engine/Utils.hpp"
#include <Windows.h>
#include <glm.hpp>
#include "Level.h"

Game::Game()
{
	Logger::Log("Game constructor called");
	isRunning = false;
}

Game::~Game()
{
	Logger::Log("Game destructor called");
}

void Game::Start()
{
	//SDL setup
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Err("Error initializing SDL!");
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //bilinear filtering

	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (!window)
	{
		Logger::Err("Error creating SDL Window!");
		return;
	}

#ifdef VSYNC
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
#else
	renderer = SDL_CreateRenderer(window, -1, 0);
#endif // VSYNC

	if (!renderer)
	{
		Logger::Err("Error creating SDL Renderer!");
		return;
	}

	Logger::Log("SDL Initialized !");


	//Engine setup
	SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
	input = std::make_unique<Input>();
	assetManager = std::make_unique<AssetManager>(renderer);

	//Game setup
	//Keyboard bindings
	input->BindKey(Action::MoveLeft, SDL_SCANCODE_LEFT);
	input->BindKey(Action::MoveRight, SDL_SCANCODE_RIGHT);
	input->BindKey(Action::MoveUp, SDL_SCANCODE_UP);
	input->BindKey(Action::MoveDown, SDL_SCANCODE_DOWN);
	input->BindKey(Action::Shoot, SDL_SCANCODE_SPACE);

	//Gamepad mapping (assuming Xbox-style controller)
	input->BindButton(Action::MoveLeft, SDL_CONTROLLER_BUTTON_DPAD_LEFT);
	input->BindButton(Action::MoveRight, SDL_CONTROLLER_BUTTON_DPAD_RIGHT);
	input->BindButton(Action::MoveUp, SDL_CONTROLLER_BUTTON_DPAD_UP);
	input->BindButton(Action::MoveDown, SDL_CONTROLLER_BUTTON_DPAD_DOWN);
	input->BindButton(Action::Shoot, SDL_CONTROLLER_BUTTON_A);

	assetManager->AddTexture("Ship", "./Assets/Images/Ship.tga");
	assetManager->AddTexture("Bullet", "./Assets/Images/Bullet.tga");
	assetManager->AddTexture("Tileset", "./Assets/Images/Tileset.tga");

	//Create level
	level = std::make_unique<Level>(assetManager->GetTexture("Tileset"), "./Assets/Maps/Level01.csv", 8, 64);

	//create player
	player = std::make_unique<Player>(	glm::vec2(512 - 32, 900),
										assetManager->GetTexture("Ship"),
										assetManager->GetTexture("Bullet"),
										input);
	player->dim = glm::vec2(64, 64);
	player->speed = 400;
	player->animSpeed = 20;

	isRunning = true;
}

void Game::ProcessInput()
{
	input->ProcessInput();

	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
			case SDL_QUIT: isRunning = false; break;
			case SDL_KEYDOWN: if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
		}
	}
}

void Game::Update()
{
#ifdef CAP_FPS
	uint64_t timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks64() - millisecondPreviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME)
		SDL_Delay(timeToWait); //yield to other processes
#endif // CAP_FPS

	float deltaTime = (SDL_GetTicks64() - millisecondPreviousFrame) / 1000.0f;
	millisecondPreviousFrame = SDL_GetTicks64();

	//perform update
	level->Update(deltaTime);
	player->Update(deltaTime);
}

void Game::Render()
{
	//clear draw buffer
	SDL_SetRenderDrawColor(renderer, 80, 60, 40, 255);
	SDL_RenderClear(renderer);

	//perform rendering
	level->Render(renderer);
	player->Render(renderer);

	//wait for VSync (or not) and swap buffers -> draw becomes display and vice-versa
	SDL_RenderPresent(renderer);
}

void Game::Run()
{
	while (isRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Quit()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	Logger::Log("SDL closed !");
}
