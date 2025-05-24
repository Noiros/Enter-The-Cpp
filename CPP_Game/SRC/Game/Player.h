#pragma once
#include "../Engine/Node.h"
#include <memory>

enum class EntityType { PLAYER, ENEMY };

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

class Player : public Node
{
public:
    float speed;
    int animSpeed; //frames per second
    std::unique_ptr<InputManager>& input;

    Player(vec2 p, SDL_Texture* t, SDL_Texture* bt, std::unique_ptr<InputManager>& i) : Node(p, vec2(0, 0),
        EntityType::PLAYER, t), input(i), bulletTexture(bt)
    {
        Bullet::texture = bulletTexture;
        head = &bullets[0]; //head
        for (int i = 0; i < poolSize - 1; i++) bullets[i].state.next = &bullets[i + 1];
        bullets[poolSize - 1].state.next = nullptr; //tail
    }

    ~Player() override = default;

    void Update(float deltaTime) override;
    void Render(SDL_Renderer* renderer) override;

    void Shoot(vec2 pos, vec2 vel);

private:
    Bullet* head;
    SDL_Texture* bulletTexture;
    static constexpr uint32_t poolSize = 1000;
    Bullet bullets[poolSize];
};
