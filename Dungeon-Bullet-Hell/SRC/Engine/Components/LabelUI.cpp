#include "LabelUI.h"
#include <SDL_ttf.h>

void LabelUI::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    ComponentUI::Render(renderer, cameraPos, cameraScale);

    TTF_Font* font = TTF_OpenFont("./Assets/Fonts/Poppins-Black.ttf", fontSize);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, text.c_str(), textColor);
    if (!textSurface) {
        TTF_CloseFont(font);
        return;
    }

    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (!textTexture) {
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }

    int textW = 0;
    int textH = 0;
    SDL_QueryTexture(textTexture, NULL, NULL, &textW, &textH);

    SDL_Rect renderQuad = { x, y, textW, textH }; 

    SDL_RenderCopy(renderer, textTexture, NULL, &renderQuad);
    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}
