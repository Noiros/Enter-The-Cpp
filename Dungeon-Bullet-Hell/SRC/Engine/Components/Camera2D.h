#pragma once

#include "Component2D.h"
#include "Transform2D.h"

class Camera2D : public Component2D
{
public:
    
    void SetCurrent();
    glm::vec2 GetCameraPos() { return cameraPos; }
    float GetCameraScale() { return CameraScale; }

    float CameraLag = 2.0f;
    float CameraScale = 1.0f;

    void Ready();
    void Update(float deltaTime);

private:
    glm::vec2 cameraPos = {0, 0};
    Transform2D* transform;
};
