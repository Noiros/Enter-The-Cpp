#include "TextureRect.h"

#include "Transform.h"
#include "../Logger.h"


void TextureRect::Update(float deltaTime)
{
}

void TextureRect::Ready()
{
}

void TextureRect::Render(SDL_Renderer* renderer)
{
    //compute animation frame
    uint32_t animFrame = (SDL_GetTicks64() * animSpeed / 1000) % 2; //2 frames for this anim
    animFrame = 1;

    //source rectangle for the blit
    SDL_Rect src = {static_cast<int>(animFrame * 64), 0, 64, 64};

    //dest rectangle
 
    Transform transform = ParentNode->GetComponent<Transform>();
    
    //SDL_FRect dst = {transform->position.x, transform->position.y, transform->size.x, transform->size.y};
    SDL_FRect dst = {0, 0, 640, 640};
    Logger::Log("Rendering texture");

    
    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyF(renderer, texture, &src, &dst);
}
