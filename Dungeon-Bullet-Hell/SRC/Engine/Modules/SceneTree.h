#pragma once
#include <memory>
#include <SDL_render.h>
#include <vector>
#include <map>
#include "../GameObject.h"

class SceneTree
{
    public:
        SceneTree() = default;
        ~SceneTree() = default;

        void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale);
        void Update(float deltaTime);
        void ProcessPendingGameObjects();

        template<typename T>
        inline T& GetGameObjectByName(std::string_view name)
        {
            auto ptr = gameObjectByName.at(name);
            return *static_cast<T*>(ptr);
        }
    
        template <class T, class... Args>
        T* AddGameObject(std::string_view objectName = "Default", Args&&... args)
        {
            T* newGameObject = new T(std::forward<Args>(args)...);
            std::unique_ptr<GameObject> unique_ptr { newGameObject };
            pendingGameObjects.emplace_back(std::move(unique_ptr));
            gameObjectByName.emplace(objectName, newGameObject);
            newGameObject->SetName(objectName);
            newGameObject->Ready();
            return newGameObject;
        }

        void DestroyGameObject(GameObject* gameObject);

        // Create singleton
        static void SetInstance(SceneTree* instance) { s_instance = instance; };
        static SceneTree& Get() { return *s_instance; };
        SceneTree(const SceneTree&) = delete;
        SceneTree& operator=(const SceneTree&) = delete;

    private:
        std::map<std::string_view, GameObject*> gameObjectByName;
        std::vector<std::unique_ptr<GameObject>> gameObjects;
        std::vector<std::unique_ptr<GameObject>> pendingGameObjects;
        //std::vector<std::unique_ptr<GameObject>> pendingRemoveGameObjects;
        static SceneTree* s_instance;
};
