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

void Engine::SetInstance(Engine* instance)
{
    if (s_instance != nullptr && instance != nullptr && s_instance != instance)
    {
        // Gérer l'erreur ou l'avertissement si une instance est déjà définie
        // Vous pouvez aussi lancer une exception ou un assert ici si c'est une erreur critique.
    }
    s_instance = instance;
}

Engine& Engine::GetInstance()
{
    if (s_instance == nullptr)
    {
        // Gérer l'erreur si GetInstance() est appelé avant que l'Engine ne soit créé
        // Vous pouvez lancer une exception ou un assert pour éviter des comportements indéfinis.
        // Ou, si vous voulez une initialisation paresseuse, vous pourriez créer l'instance ici,
        // mais cela irait à l'encontre de votre besoin de la créer dans main().
    }
    return *s_instance;
}




void Engine::Setup()
{
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    // Setup Scene Tree
    sceneTree = std::make_unique<SceneTree>();
    
    // Setup Input Manager
    inputManager = std::make_unique<InputManager>();

    // Setup Rendering Server
    renderingServer = std::make_unique<RenderingServer>();
    renderingServer->Setup();

    // Setup Resources Manager
    resourcesManager = std::make_unique<ResourcesManager>(renderingServer->renderer);

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
    SDL_DestroyRenderer(renderingServer->renderer);
    SDL_DestroyWindow(renderingServer->window);
    SDL_Quit();
    Logger::Log("SDL closed !");
}

void Engine::Update()
{
    inputManager->ProcessInput();

#ifdef CAP_FPS
    uint64_t timeToWait = MILLISEC_PER_FRAME - (SDL_GetTicks64() - millisecondPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISEC_PER_FRAME)
        SDL_Delay(timeToWait); //yield to other processes
#endif // CAP_FPS

    float deltaTime = (SDL_GetTicks64() - millisecondPreviousFrame) / 1000.0f;
    millisecondPreviousFrame = SDL_GetTicks64();

    renderingServer->Clear();
    sceneTree->UpdateNodes(renderingServer->renderer, deltaTime);    
    renderingServer->Render();
    
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
}