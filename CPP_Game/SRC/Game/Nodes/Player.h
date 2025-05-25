#pragma once

#include "../../Engine/Node.h"
#include "../../Engine/Engine.h"
#include "../../Engine/Components/Movement.h"
#include <memory>

class Camera2D;
class TextureRect;

class Player : public Node
{
public:
    float speed = 100.0f;
    int animSpeed; //frames per second

    InputManager* inputManager;

    void Update(float deltaTime) override;
    void Ready() override;

    void Shoot();

private:
    Movement* movement;
    TextureRect* textureRect;
    Camera2D* camera;
    
    glm::vec2 moveDir = glm::vec2(0, 0);
    glm::vec2 lookDir = glm::vec2(0, 0);
};
