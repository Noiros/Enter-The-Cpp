#pragma once
#include <memory>

#include "InputManager.h"
#include "PhysicsServer.h"
#include "RenderingServer.h"
#include "ResourcesManager.h"
#include "SceneTree.h"


class Engine
{
    public:
        std::unique_ptr<SceneTree> sceneTree;
        std::unique_ptr<PhysicsServer> physicsServer;
        std::unique_ptr<RenderingServer> renderingServer;
        std::unique_ptr<ResourcesManager> resourcesManager;
        std::unique_ptr<InputManager> inputManager;

        //std::unique_ptr<Game> game;
    
        Engine();
        ~Engine();

        static void SetInstance(Engine* instance);
        static Engine& GetInstance();
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
