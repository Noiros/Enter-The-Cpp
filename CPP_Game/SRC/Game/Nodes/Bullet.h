#pragma once

#include "../../Engine/Node.h"
#include <memory>


class Bullet : public Node
{    
    public:    
        void Ready() override;
        void Update(float deltaTime) override;
};


/*
struct BulletParams
{
    glm::vec2 pos = {0, 0};
    glm::vec2 vel = {0, 0};
};

union BulletState
{
    BulletParams params;
    class Bullet* next = nullptr; //forward declaration of Bullet. Pointer to the next available bullet.
};

class Bullet //simpler class does not inherit from entity
{
public:
    bool Update(float deltaTime); //true when destroyed
    void Render(SDL_Renderer* renderer);

    BulletState state;
    bool isActive = false;
    inline static SDL_Texture* texture = nullptr;

private:
    inline static constexpr glm::vec2 dim = {8, 8}; //shared across all instances
    inline static constexpr SDL_Color color = {255, 80, 5};
};
*/
