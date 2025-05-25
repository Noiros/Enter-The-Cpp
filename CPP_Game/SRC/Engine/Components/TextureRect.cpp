#include "TextureRect.h"

#include "Transform.h"
#include "../Engine.h"


TextureRect::TextureRect(std::string_view name)
{
    texture = ResourcesManager::GetInstance().GetTexture(name);
}

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
    animFrame = 0;

    //source rectangle for the blit
    SDL_Rect src = {static_cast<int>(animFrame * 64), 0, 64, 64};
    
    //dest rectangle
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform* transform = sceneTree->GetComponent<Transform>(ParentNode);

    glm::ivec2 centerPos = {int(transform->size.x * transform->anchor.x), int(transform->size.y * transform->anchor.y)};
    SDL_Point center = {centerPos.x, centerPos.y};
    SDL_Rect dst = {int(transform->position.x) - centerPos.x, int(transform->position.y) - centerPos.y, int(transform->size.x), int(transform->size.y)};

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyEx(renderer, texture, &src, &dst, transform->rotation, &center, SDL_FLIP_NONE);
}
