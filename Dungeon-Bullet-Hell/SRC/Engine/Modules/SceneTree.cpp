#include "SceneTree.h"

#include "../GameObject.h"
#include "../../Game/Game.h"

SceneTree* SceneTree::s_instance = nullptr;

void SceneTree::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    for (auto& gameObject : gameObjects)
    {
        gameObject->Render(renderer, cameraPos, cameraScale);
        for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
        {
            comp->Render(renderer, cameraPos, cameraScale);
        }
    }
}

void SceneTree::Update(float deltaTime)
{
    for (std::unique_ptr<GameObject>& gameObject : gameObjects)
    {
        gameObject->Update(deltaTime);
        for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
        {
            comp->Update(deltaTime);
        }
    }

    ProcessPendingGameObjects();
}

void SceneTree::ProcessPendingGameObjects()
{
    if (!pendingGameObjects.empty())
    {
        for (auto& newGameObjectUniquePtr : pendingGameObjects)
        {
            if (newGameObjectUniquePtr)
            {
                GameObject* rawPtr = newGameObjectUniquePtr.get();
                gameObjects.emplace_back(std::move(newGameObjectUniquePtr));
            }
        }
        pendingGameObjects.clear();
    }
}

