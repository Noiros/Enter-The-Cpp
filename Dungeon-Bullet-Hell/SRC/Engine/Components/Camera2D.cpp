#include "Camera2D.h"

#include <cmath>

#include "Transform2D.h"
#include "../Modules/RenderingServer.h"
#include "../GameObject.h"

void Camera2D::SetCurrent()
{
    RenderingServer::Get().camera = this;
}

void Camera2D::Ready()
{
    transform = &gameObject->GetComponent<Transform2D>();
    SetCurrent();
}

void Camera2D::Update(float deltaTime)
{
    cameraPos.x = std::lerp(cameraPos.x, transform->position.x, (deltaTime * CameraLag));
    cameraPos.y = std::lerp(cameraPos.y, transform->position.y, (deltaTime * CameraLag));
}
