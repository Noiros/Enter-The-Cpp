#include "SceneTree.h"

#include "../../Game/Game.h"
#include "../Logger.h"

SceneTree* SceneTree::s_instance = nullptr;

void SceneTree::Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale)
{
    std::vector<Component*> componentsToRender;
    for (auto& gameObject : gameObjects)
    {
        if (gameObject->IsActive())
        {
            for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
            {
                componentsToRender.push_back(comp.get());
            }
        }
    }

    std::sort(componentsToRender.begin(), componentsToRender.end(), 
              [](Component* a, Component* b) {
                  return a->ZOrder < b->ZOrder;
              });

    for (Component* comp : componentsToRender)
    {
        comp->Render(renderer, cameraPos, cameraScale);
    }

    for (auto& gameObject : gameObjects)
    {
        if (gameObject->IsActive())
        {
            gameObject->Render(renderer, cameraPos, cameraScale);
        }
    }
}


void SceneTree::Update(float deltaTime)
{
    for (std::unique_ptr<GameObject>& gameObject : gameObjects)
    {
        if (gameObject->IsActive())
        {
            for (std::unique_ptr<Component>& comp : *gameObject->GetAllComponents())
            {
                comp->Update(deltaTime);
            }
            gameObject->Update(deltaTime);
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

void SceneTree::RegisterGameObjectFactory(int id, GameObjectCreator creator) {
    objectFactories[id] = creator;
}

std::unique_ptr<GameObject> SceneTree::CreateGameObjectByID(int id, std::string_view name) {
    auto it = objectFactories.find(id);
    if (it != objectFactories.end()) {
        std::unique_ptr<GameObject> newObj = it->second(name);
        if (newObj) {
            newObj->SetName(name);
        }
        return newObj;
    }
    return nullptr;
}
