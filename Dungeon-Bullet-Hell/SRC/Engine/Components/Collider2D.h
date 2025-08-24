#pragma once

#include "Component2D.h"
#include "Transform2D.h"
#include "../Resources/CollisionShape.h"

class Collider2D : public Component2D
{
public:
    Collider2D(CollisionShape shape) : collisionShape(shape) {};
    
    CollisionShape collisionShape;
    int layer = 0;
    bool isTrigger = false;

    void Ready();
    void Update(float deltaTime);
    void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);

private:
    Transform2D* transform;
};
