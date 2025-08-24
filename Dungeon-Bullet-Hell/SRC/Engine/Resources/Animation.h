#pragma once
#include <vector>

#include "SpriteSheet.hpp"

struct Animation
{
    Animation(std::vector<int> f, SpriteSheet sp, float duration = 0.5f) : frames(f), sprite(sp), frameDuration(duration) {}
    
    SpriteSheet sprite;
    std::vector<int> frames;
    float frameDuration = 0.5f;
};
