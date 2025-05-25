#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vector>
#include "Component.h"


class RenderingServer
{
    public:
        RenderingServer();
        ~RenderingServer() {};
    
        static void SetInstance(RenderingServer* instance) { s_instance = instance; };
        static RenderingServer& GetInstance() { return *s_instance; };
        RenderingServer(const RenderingServer&) = delete;
        RenderingServer& operator=(const RenderingServer&) = delete;

        SDL_Renderer* GetRenderer() const { return renderer; }
        void Render();
        void Clear();

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        
    private:
        static RenderingServer* s_instance;
};
