#pragma once

#include <SDL.h>
#include "../Engine/Modules/ResourcesManager.h"
#include "../Engine/Modules/InputManager.h"
#include "GameObject/Player.h"
#include "../Engine/Engine.h"


#define VSYNC //FPS will be determined by the display refresh rate
//#define CAP_FPS //If defined, this will limit to the set frame rate below. Otherwise, only the VSYNC will be the limiting factor.
//#define DEBUG_MODE //Show collisions and other debug info

constexpr uint32_t FPS = 30; //Only used if CAP_FPS
constexpr uint32_t MILLISEC_PER_FRAME = 1000 / FPS;

constexpr uint32_t DISPLAY_WIDTH = 1024;
constexpr uint32_t DISPLAY_HEIGHT = 1024;

enum class Action { MoveLeft, MoveRight, MoveUp, MoveDown, Shoot, Dash };

class TileMap2D;

class Game
{
public:
    Game();
    ~Game();

    InputManager* inputManager;
    ResourcesManager* resourcesManager;
    SceneTree* sceneTree;
    
    void GenMap();
    void Start(Engine* engine);

private:
    Player* player;
};
