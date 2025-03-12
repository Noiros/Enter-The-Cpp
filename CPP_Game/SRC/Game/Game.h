#pragma once
#include <SDL.h>
#include <memory>
#include "../Engine/Node.h"

//#define VSYNC
//#define CAP_FPS

const uint32_t FPS = 60;
const uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

const uint32_t DISPLAY_WIDTH = 1024;
const uint32_t DISPLAY_HEIGHT = 1024;

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

		bool isRunning;
		uint64_t millisecondPerviousFrame = 0;

		std::vector<std::unique_ptr<Node>> nodes;

		void ProcessInput();
		void Update();
		void Render();
};