#pragma once

#include <SDL.h>
#include "../Engine/Node.h"
#include "../Engine/Modules/ResourcesManager.h"
#include "../Engine/Modules/InputManager.h"
#include "../Engine/Modules/RenderingServer.h"
#include <vector>
#include "Nodes/Player.h"
#include "../Engine/Engine.h""


#define VSYNC //FPS will be determined by the display refresh rate
//#define CAP_FPS //If defined, this will limit to the set frame rate below. Otherwise, only the VSYNC will be the limiting factor.

constexpr uint32_t FPS = 30; //Only used if CAP_FPS
constexpr uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

constexpr uint32_t DISPLAY_WIDTH = 1024;
constexpr uint32_t DISPLAY_HEIGHT = 1024;

enum class Action { MoveLeft, MoveRight, MoveUp, MoveDown, Shoot };

class Level;

class Game
{
public:
    Game();
    ~Game();

    void Start(Engine* engine);
    void Quit();

private:
    Player* player;

    //Level data
    std::unique_ptr<Level> level; //this could be a vector of levels

    void ProcessInput();
    void Update();
};
