#include "Engine.h"
#include "Logger.h"

#include <Windows.h>

Engine* Engine::s_instance = nullptr;

Engine::Engine()
{
    Logger::Log("Engine constructor called");
}

Engine::~Engine()
{
    Logger::Log("Engine destructor called");
    s_instance = nullptr;
}


void Engine::Setup()
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);
    
    // Setup Scene Tree
    SceneTree::SetInstance(&sceneTree);

    // Setup Input Manager
    InputManager::SetInstance(&inputManager);

    // Setup Rendering Server
    RenderingServer::SetInstance(&renderingServer);

    // Setup Resources Manager
    ResourcesManager::SetInstance(&resourcesManager);

    // Setup Physics Server
    PhysicsServer::SetInstance(&physicsServer);

    isRunning = true;
    Logger::Log("Engine setup done !");
}

void Engine::Run()
{
    while (isRunning)
    {
        Update();
    }
}

void Engine::Quit()
{
    SDL_DestroyRenderer(renderingServer.renderer);
    SDL_DestroyWindow(renderingServer.window);
    SDL_Quit();
    Logger::Log("SDL closed !");
}

void Engine::Update()
{
    inputManager.ProcessInput();

#ifdef CAP_FPS
    uint64_t timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks64() - millisecondPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME)
        SDL_Delay(timeToWait); //yield to other processes
#endif // CAP_FPS

    float deltaTime = (SDL_GetTicks64() - millisecondPreviousFrame) / 1000.0f;
    millisecondPreviousFrame = SDL_GetTicks64();

    renderingServer.Clear();
    uint64_t startUpdateMillis = SDL_GetTicks64();
    sceneTree.Update(deltaTime);
    millisUpdateFrame = SDL_GetTicks64() - startUpdateMillis;
    uint64_t startRenderMillis = SDL_GetTicks64();
    renderingServer.Render();
    millisRenderFrame = SDL_GetTicks64() - startRenderMillis;

    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent))
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT: isRunning = false;
            break;
        case SDL_KEYDOWN: if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
            break;
        }
    }
    millisFrame = SDL_GetTicks64() - millisecondPreviousFrame;
}
