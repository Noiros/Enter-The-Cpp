#pragma once
#include <map>

#include "../Resources/Animation.h"

#include "Component2D.h"

class AnimatedSprite2D : public Component2D
{
    public:
        AnimatedSprite2D(SpriteSheet sheet) : spriteSheet(sheet) {};

        SpriteSheet spriteSheet;
    
        void Ready() override;
        void Update(float deltaTime) override;
        uint32_t CalculateAnimationFrame();
        void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) override;

        void PlayAnimation(std::string_view name);
        void AddAnimation(std::string_view name, Animation anim);

        std::map<std::string_view, Animation> animations;

    private:
        Animation* currentAnimation;
};

