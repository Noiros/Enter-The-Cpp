#pragma once

#include "Components/Transform.h"

// Forward declarations si nécessaires
struct SDL_Renderer;
enum class EntityType; // Conserve la déclaration si elle est utilisée ailleurs

class Node
{
public:
    bool toBeDestroyed = false;

    Transform* transform;

    Node()
    {
    }

    virtual ~Node()
    {
    }

    virtual void Ready() = 0;
    virtual void Update(float deltaTime) = 0;
};
