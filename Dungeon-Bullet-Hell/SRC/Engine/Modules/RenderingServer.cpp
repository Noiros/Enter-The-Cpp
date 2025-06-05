#include "RenderingServer.h"

#include <algorithm>
#include <fwd.hpp>
#include <SDL_render.h>
#include <SDL_ttf.h>

#include "../../Game/Game.h"
#include "SceneTree.h"

#include "../Logger.h"

RenderingServer* RenderingServer::s_instance = nullptr;


RenderingServer::RenderingServer()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error initializing SDL!");
        return;
    }

    window = SDL_CreateWindow("My Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DISPLAY_WIDTH, DISPLAY_HEIGHT,
                              SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        Logger::Err("Error creating SDL Window!");
        return;
    }
    TTF_Init();

#ifdef VSYNC
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
#else
    renderer = SDL_CreateRenderer(window, -1, 0);
#endif // VSYNC

    if (!renderer)
    {
        Logger::Err("Error creating SDL Renderer!");
        return;
    }

    Logger::Log("Rendering server initialized.");
}

void RenderingServer::Clear()
{
    //clear draw buffer
    SDL_SetRenderDrawColor(renderer, 29, 28, 43, 255);
    SDL_RenderClear(renderer);
}

void RenderingServer::Render()
{
    if (camera != NULL)
    {
        glm::vec2 cameraPos = camera->GetCameraPos() - glm::vec2(DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2);

        SceneTree::Get().Render(renderer, cameraPos, camera->GetCameraScale());
        
        SDL_RenderPresent(renderer);
    }
}