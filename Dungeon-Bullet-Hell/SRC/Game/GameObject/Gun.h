#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Components/Sprite2D.h"

enum GunTeam { PLAYER, ENEMY };

class Gun : public GameObject
{
public:
    int bulletsPerShot = 1;
    float fireRate = 0.1f;
    float bulletSpeed = 2.0f;
    float gunSpread = 20.0;
    glm::vec2 gunHandle = {20, 0};
    GunTeam team = PLAYER;
    
    Sprite2D* sprite;
    GameObject* parent;
    glm::vec2 lookAtDir;

    Gun(GameObject* s) : parent(s) {};
    void Ready() override;
    void Update(float deltaTime) override;
    void Shoot();

private:
    uint32_t lastFire;
};
