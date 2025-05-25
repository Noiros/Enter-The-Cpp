#include "AnimatedSprite2D.h"

#include "Transform2D.h"
#include "../Engine.h"

void AnimatedSprite2D::Ready()
{
    
}

void AnimatedSprite2D::PlayAnimation(std::string_view animationName)
{
    if (animations.contains(animationName))
    {
        currentAnimation = &animations.at(animationName);        
    }
}

void AnimatedSprite2D::AddAnimation(std::string_view name, Animation anim)
{
    animations.emplace(name, anim);
}


void AnimatedSprite2D::Update(float deltaTime)
{
    
}

uint32_t AnimatedSprite2D::CalculateAnimationFrame()
{
    uint64_t currentTicks = SDL_GetTicks64();
    float timeInSeconds = static_cast<float>(currentTicks) / 1000.0f;
    uint32_t numberOfFrames = static_cast<uint32_t>(currentAnimation->frames.size());
    return static_cast<uint32_t>(fmod(timeInSeconds / currentAnimation->frameDuration, numberOfFrames));
}

void AnimatedSprite2D::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    SceneTree* sceneTree = &SceneTree::GetInstance();
    Node* ParentNode = sceneTree->GetRootNode(this);
    Transform2D* transform = sceneTree->GetComponent<Transform2D>(ParentNode);
    
    uint32_t animFrame = CalculateAnimationFrame();
    glm::ivec2 pos = currentAnimation->sprite.GetFramePosition(currentAnimation->frames[animFrame]);
    SDL_Rect textureSrc = {pos.x, pos.y, int(currentAnimation->sprite.tileSize.x), int(currentAnimation->sprite.tileSize.y)};
    
    //dest rectangle
    glm::ivec2 centerPos = {int(transform->size.x * transform->anchor.x), int(transform->size.y * transform->anchor.y)};
    SDL_Point center = {centerPos.x, centerPos.y};
    SDL_Rect dst = {int(transform->position.x) - centerPos.x - int(cameraPos.x), int(transform->position.y) - centerPos.y - int(cameraPos.y), int(transform->size.x * cameraScale), int(transform->size.y * cameraScale)};

    //blit
    SDL_SetTextureBlendMode(spriteSheet.texture, SDL_BLENDMODE_BLEND); //alpha blend
    SDL_RenderCopyEx(renderer, spriteSheet.texture, &textureSrc, &dst, transform->rotation, &center, SDL_FLIP_NONE);
    
}
