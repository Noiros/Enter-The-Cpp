#pragma once

#include "Components/Transform2D.h"

// Forward declarations si nécessaires
struct SDL_Renderer;
enum class EntityType; // Conserve la déclaration si elle est utilisée ailleurs

class Node
{
public:
    bool toBeDestroyed = false;

    Transform2D* transform;

    Node() = default;
    virtual ~Node() = default;

    virtual void Ready() = 0;
    virtual void Update(float deltaTime) = 0;
};
