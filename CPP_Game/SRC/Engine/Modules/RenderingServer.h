#pragma once
#include <SDL_rect.h>
#include <SDL_render.h>
#include <vec2.hpp>
#include <vector>

#include "../Component.h"
#include "../Components/Camera2D.h"


class RenderingServer
{
    public:
        RenderingServer();

        ~RenderingServer()
        {
        };
    
        static void SetInstance(RenderingServer* instance) { s_instance = instance; };
        static RenderingServer& Get() { return *s_instance; };
        RenderingServer(const RenderingServer&) = delete;
        RenderingServer& operator=(const RenderingServer&) = delete;

        SDL_Renderer* GetRenderer() const { return renderer; }
        void UpdateComponents(std::vector<Component*> components);
        void Render();
        void Clear();

        SDL_Window* window = nullptr;
        SDL_Renderer* renderer = nullptr;
        Camera2D* camera;

    private:
        static RenderingServer* s_instance;
        std::vector<Component*> orderedComponents;
};
