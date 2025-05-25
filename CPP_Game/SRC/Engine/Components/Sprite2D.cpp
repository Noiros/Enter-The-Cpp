#include "Sprite2D.h"

#include "Transform2D.h"
#include "../Engine.h"


Sprite2D::Sprite2D(std::string_view name)
{
    texture = ResourcesManager::GetInstance().GetTexture(name);
}

void Sprite2D::Update(float deltaTime)
{
}

void Sprite2D::Ready()
{
}

void Sprite2D::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    //compute animation frame
    uint32_t animFrame = (SDL_GetTicks64() * animSpeed / 1000) % 2; //2 frames for this anim
    animFrame = 0;

    //source rectangle for the blit
    SDL_Rect src = {static_cast<int>(animFrame * 64), 0, 64, 64};
    
    //dest rectangle
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform2D* transform = sceneTree->GetComponent<Transform2D>(ParentNode);

    glm::ivec2 centerPos = {int(transform->size.x * transform->anchor.x), int(transform->size.y * transform->anchor.y)};
    SDL_Point center = {centerPos.x, centerPos.y};
    SDL_Rect dst = {int(transform->position.x) - centerPos.x - int(cameraPos.x), int(transform->position.y) - centerPos.y - int(cameraPos.y), int(transform->size.x * cameraScale), int(transform->size.y * cameraScale)};

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyEx(renderer, texture, &src, &dst, transform->rotation, &center, SDL_FLIP_NONE);
}
