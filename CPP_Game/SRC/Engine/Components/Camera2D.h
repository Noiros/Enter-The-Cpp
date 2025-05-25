#pragma once

#include "Component2D.h"

class Camera2D : public Component2D
{
public:
    Camera2D();
    
    void SetCurrent();
    
    glm::vec2 GetCameraPos() { return cameraPos; }
    float GetCameraScale() { return CameraScale; }

    float CameraLag = 1.0f;
    float CameraScale = 1.0f;

    void Update(float deltaTime) override;

private:
    glm::vec2 cameraPos = {0, 0};
};
