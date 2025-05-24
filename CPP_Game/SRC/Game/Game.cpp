#include "Game.h"
#include <iostream>
#include <SDL.h>
#include "Player.h"
#include <Windows.h>
#include <memory>

#include "../Engine/Logger.h"
#include "../Engine/Utils.hpp"
#include "../Engine/ResourcesManager.h"

Game::Game() {
	Logger::Log("Game constructor called");
	isRunning = false;
}

Game::~Game() {
	Logger::Log("Game destructor called");
}

void Game::Start() {
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
		Logger::Err("Error initializing SDL");
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"); //bilinear filtering

	window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (!window) {
		Logger::Err("Error creating SDL Window");
		return;
	}

#ifdef VSYNC
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
#else
	renderer = SDL_CreateRenderer(window, -1, 0);
#endif // VSYNC

	if (!renderer) {
		Logger::Err("Error creating SDL Renderer");
		return;
	}

	Logger::Log("SDL Initialized");

	//Engine setup
	input = std::make_unique<Input>();
	resourcesManager = std::make_unique<ResourcesManager>(renderer);

	//Game setup
	SetThreadPriority(GetCurrentThread(), SDL_THREAD_PRIORITY_TIME_CRITICAL);
	isRunning = true;

	resourcesManager->LoadTexture("./Datas/Assets/Ship.tga");
	for (size_t i = 0; i < 1; i++) {
		SDL_Texture* texture = resourcesManager->GetTexture("./Datas/Assets/Ship.tga");
		std::unique_ptr<Player> player = std::make_unique<Player>(Utils::randVec2Range(1, DISPLAY_WIDTH - 10), Utils::randVec2Range(-500, 500), Utils::randColor(), texture);
		player->size = glm::vec2(64, 64);
		nodes.push_back(std::move(player)); // Transfer ownership to the vector
	}
}

void Game::ProcessInput() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		switch (sdlEvent.type) {
			case SDL_QUIT: isRunning = false; break;
			case SDL_KEYDOWN: if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false; break;
		}
	}
}

void Game::Update() {
#ifdef CAP_FPS
	uint64_t timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks64() - millisecondPerviousFrame);
	if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME) {
		SDL_Delay(timeToWait); //yield to other processes
	}
#endif //CAP_FPS

	float deltaTime = (SDL_GetTicks64() - millisecondPerviousFrame) / 1000.0f;
	millisecondPerviousFrame = SDL_GetTicks64();

	//update entities
	for (const auto& node : nodes) {
		node->Update(deltaTime);
	}

}

void Game::Render() {
	SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
	SDL_RenderClear(renderer);

	for (const auto& node : nodes) {
		Node2D* visual_node = dynamic_cast<Node2D*>(node.get());

		SDL_Rect size = { visual_node->position.x, visual_node->position.y, visual_node->size.x, visual_node->size.y };
		SDL_Rect rect = { 0, 0, visual_node->size.x * visual_node->scale.x, visual_node->size.y * visual_node->scale.y };

		SDL_SetTextureColorMod(visual_node->texture, visual_node->modulate.r, visual_node->modulate.g, visual_node->modulate.b);
		SDL_SetTextureBlendMode(visual_node->texture, SDL_BlendMode::SDL_BLENDMODE_BLEND);
		SDL_RenderCopy(renderer, visual_node->texture, &rect, &size);

		//SDL_SetRenderDrawColor(renderer, visual_node->modulate.r, visual_node->modulate.g, visual_node->modulate.b, visual_node->modulate.a);
		//SDL_RenderFillRectF(renderer, &rect);
	}

	SDL_RenderPresent(renderer);
}

void Game::Run() {
	while (isRunning) {
		ProcessInput();
		Update();
		Render();
	}
}

void Game::Quit() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}