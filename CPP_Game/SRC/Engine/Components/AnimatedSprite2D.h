#pragma once
#include <map>

#include "../Resources/Animation.h"

#include "Component2D.h"
#include "Transform2D.h"

class AnimatedSprite2D : public Component2D
{
    public:
        AnimatedSprite2D(SpriteSheet sheet) : spriteSheet(sheet) {};

        SpriteSheet spriteSheet;
    
        void Ready();
        void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);

        uint32_t CalculateAnimationFrame();
        void PlayAnimation(std::string_view name);
        void AddAnimation(std::string_view name, Animation anim);


    private:
        std::map<std::string_view, Animation> animations;
        Animation* currentAnimation;
        Transform2D* transform;
};

