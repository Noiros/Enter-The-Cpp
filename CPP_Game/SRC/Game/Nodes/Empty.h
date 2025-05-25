#pragma once
#include <SDL_render.h>
#include <string>
#include "../../Engine/Node.h"

class Empty : public Node
{
        public:
                void Ready() override {};
                void Update(float deltaTime) override {};
                Empty() {};
                ~Empty() {};
};
