#pragma once
#include <SDL_render.h>
#include <string>

#include "ComponentUI.h"

class LabelUI : public ComponentUI
{
public:
    std::string text;
    int fontSize;
    int x, y;
    SDL_Color textColor = {255, 255, 255, 255};

    LabelUI(std::string text, int fontSize, int x, int y) : text(text), fontSize(fontSize), x(x), y(y) {}

    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);
};
