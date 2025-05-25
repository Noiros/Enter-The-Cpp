#pragma once
#include "Sprite2D.h"

class AnimatedSprite2D : public Sprite2D
{
    public:
        AnimatedSprite2D(std::string_view name) : Sprite2D(name) {};
};
