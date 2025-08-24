#include "Sprite2D.h"

#include "Transform2D.h"
#include "../Engine.h"
#include "../GameObject.h"


void Sprite2D::Ready()
{
    transform = &gameObject->GetComponent<Transform2D>();
    texture = sprite.texture;
    transform->size = glm::vec2(GetTextureSize().x, GetTextureSize().y);
}

void Sprite2D::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{    
    //dest rectangle
    textureSrc = {0, 0, int(transform->size.x), int(transform->size.y)};

    glm::ivec2 centerPos = {int(transform->size.x * transform->anchor.x), int(transform->size.y * transform->anchor.y)};
    SDL_Point center = {centerPos.x, centerPos.y};
    SDL_Rect dst = {int(transform->position.x) - centerPos.x - int(cameraPos.x), int(transform->position.y) - centerPos.y - int(cameraPos.y), int(transform->size.x * cameraScale * transform->scale.x), int(transform->size.y * cameraScale * transform->scale.y)};

    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (HFlip)
    {
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_HORIZONTAL);
    }
    if (VFlip)
    {
        flip = static_cast<SDL_RendererFlip>(flip | SDL_FLIP_VERTICAL);
    }

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyEx(renderer, texture, &textureSrc, &dst, gameObject->transform->rotation, &center, flip); // Utiliser le 'flip' calculé
}


const SDL_Point Sprite2D::GetTextureSize() {
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}
