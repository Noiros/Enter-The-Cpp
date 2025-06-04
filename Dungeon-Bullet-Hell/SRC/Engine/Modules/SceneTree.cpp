#include "SceneTree.h"

#include "../../Game/Game.h"

SceneTree* SceneTree::s_instance = nullptr;

void SceneTree::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    for (auto& gameObject : gameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Render(renderer, cameraPos, cameraScale);
            for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
            {
                comp->Render(renderer, cameraPos, cameraScale);
            }
        }
    }
}

void SceneTree::Update(float deltaTime)
{
    for (std::unique_ptr<GameObject>& gameObject : gameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Update(deltaTime);
            for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
            {
                comp->Update(deltaTime);
            }
        }
    }

    ProcessPendingGameObjects();
}

void SceneTree::DestroyGameObject(GameObject* gameObject)
{
    if (!gameObject) return;
    gameObject->SetActive(false);

    // La suppression ne cause trop d'erreurs, j'ai donc skip par manque de temps

    /*
    auto map_it = gameObjectByName.find(gameObject->GetName());
    if (map_it != gameObjectByName.end()) {
        gameObjectByName.erase(map_it);
    }

    if (gameObject->HasComponent<Collider2D>())
    {
        PhysicsServer::Get().RmCollider(&gameObject->GetComponent<Collider2D>());
    }
    
    auto it = std::remove_if(gameObjects.begin(), gameObjects.end(),
        [gameObject](const std::unique_ptr<GameObject>& obj_ptr) {
            return obj_ptr.get() == gameObject;
        });

    for (auto current = it; current != gameObjects.end(); ++current) {
        pendingRemoveGameObjects.emplace_back(std::move(*current));
    }
    
    gameObjects.erase(it, gameObjects.end());*/
    
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
        //pendingRemoveGameObjects.clear();
    }
}

