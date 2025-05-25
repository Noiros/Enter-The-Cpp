#include "Sprite2D.h"

#include "Transform2D.h"
#include "../Engine.h"


void Sprite2D::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{    
    //dest rectangle
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform2D* transform = sceneTree->GetComponent<Transform2D>(ParentNode);
    textureSrc = {0, 0, int(transform->size.x), int(transform->size.y)};

    glm::ivec2 centerPos = {int(transform->size.x * transform->anchor.x), int(transform->size.y * transform->anchor.y)};
    SDL_Point center = {centerPos.x, centerPos.y};
    SDL_Rect dst = {int(transform->position.x) - centerPos.x - int(cameraPos.x), int(transform->position.y) - centerPos.y - int(cameraPos.y), int(transform->size.x * cameraScale), int(transform->size.y * cameraScale)};

    //blit
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyEx(renderer, texture, &textureSrc, &dst, transform->rotation, &center, SDL_FLIP_NONE);
}
