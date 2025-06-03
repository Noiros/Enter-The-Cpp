#pragma once
#include "../../Engine/GameObject.h"
#include "../../Engine/Components/Sprite2D.h"

class Gun : public GameObject
{
public:
    float fireRate = 0.1f;
    float bulletSpeed = 2.0f;
    float gunSpread = 2.0f;
    
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
