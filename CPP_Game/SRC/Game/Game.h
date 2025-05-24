#pragma once
#include <SDL.h>
#include <memory>

#include "../Engine/Input.h"
#include "../Engine/Node.h"
#include "../Engine/ResourcesManager.h"

//#define VSYNC
//#define CAP_FPS

const uint32_t FPS = 60;
const uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

const uint32_t DISPLAY_WIDTH = 1024;
const uint32_t DISPLAY_HEIGHT = 1024;

enum class Action { MoveLeft, MoveRight, MoveUp, MoveDown, Shoot };

class Game {
	public:
		Game();
		~Game();

		void Start();
		void Run();
		void Quit();

	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		std::unique_ptr<ResourcesManager> resourcesManager;
		std::unique_ptr<Input> input;


		bool isRunning;
		uint64_t millisecondPerviousFrame = 0;

		std::vector<std::unique_ptr<Node>> nodes;

		void ProcessInput();
		void Update();
		void Render();
};