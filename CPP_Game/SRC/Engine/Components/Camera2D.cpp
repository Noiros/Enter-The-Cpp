#include "Camera2D.h"

#include <cmath>

#include "../Modules/RenderingServer.h"
#include "../Modules/SceneTree.h"

void Camera2D::SetCurrent()
{
    RenderingServer::GetInstance().camera = this;
}

Camera2D::Camera2D()
{
    SetCurrent();
}

void Camera2D::Update(float deltaTime)
{
    glm::vec2 pos = SceneTree::GetInstance().GetComponent<Transform2D>(SceneTree::GetInstance().GetRootNode(this))->position;
    cameraPos.x = std::lerp(cameraPos.x, pos.x, (deltaTime * CameraLag));
    cameraPos.y = std::lerp(cameraPos.y, pos.y, (deltaTime * CameraLag));
}
