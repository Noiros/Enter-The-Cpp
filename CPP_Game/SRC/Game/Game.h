#pragma once

#include <SDL.h>
#include "../Engine/Nodes/Node.h"
#include "../Engine/Managers/ResourcesManager.h"
#include "../Engine/Managers/InputManager.h"
#include <vector>
#include "Player.h"

#define VSYNC //FPS will be determined by the display refresh rate
//#define CAP_FPS //If defined, this will limit to the set frame rate below. Otherwise, only the VSYNC will be the limiting factor.

const uint32_t FPS = 30;//Only used if CAP_FPS
const uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

const uint32_t DISPLAY_WIDTH = 1024;
const uint32_t DISPLAY_HEIGHT = 1024;

enum class Action { MoveLeft, MoveRight, MoveUp, MoveDown, Shoot };

class Level;

class Game
{
	public:
		Game();
		~Game();

		void Start();
		void Run();
		void Quit();

	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		std::unique_ptr<ResourcesManager> assetManager;
		std::unique_ptr<InputManager> input;
		std::unique_ptr<Player> player;

		bool isRunning;
		uint64_t millisecondPreviousFrame = 0;

		//Level data
		std::unique_ptr<Level> level; //this could be a vector of levels

		void ProcessInput();
		void Update();
		void Render();
};
