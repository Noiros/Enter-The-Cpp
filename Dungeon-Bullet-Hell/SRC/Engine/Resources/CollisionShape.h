#pragma once

struct CollisionShape
{
    CollisionShape(SDL_Rect r) : collisionShape(r) {}
    
    SDL_Rect collisionShape = {-16, -16, 32, 32};
};
