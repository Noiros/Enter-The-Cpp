#pragma once
#include <memory>

#include "Modules/InputManager.h"
#include "Modules/PhysicsServer.h"
#include "Modules/RenderingServer.h"
#include "Modules/ResourcesManager.h"
#include "Modules/SceneTree.h"


class Engine
{
public:
    PhysicsServer physicsServer;
    RenderingServer renderingServer;
    ResourcesManager resourcesManager;
    SceneTree sceneTree;
    InputManager inputManager;

    Engine();
    ~Engine();

    static void SetInstance(Engine* instance) { s_instance = instance; };
    static Engine& GetInstance() { return *s_instance; };
    Engine(const Engine&) = delete;
    Engine& operator=(const Engine&) = delete;

    void Setup();
    void Run();
    void Quit();

private:
    static Engine* s_instance;

    bool isRunning;
    uint64_t millisecondPreviousFrame = 0;

    void Update();
};
