#pragma once

#include <map>
#include <string>
#include <vector>

#include "RenderingServer.h"
#include "../Logger.h"
#include "../Node.h"
#include "../Component.h"
#include "../Components/Transform2D.h"

class SceneTree
{
public:
    SceneTree();
    ~SceneTree();

    void UpdateNodes(SDL_Renderer* renderer, float deltaTime);

    static void SetInstance(SceneTree* instance) { s_instance = instance; };
    static SceneTree& GetInstance() { return *s_instance; };
    SceneTree(const SceneTree&) = delete;
    SceneTree& operator=(const SceneTree&) = delete;

    template <class N, class... Args>
    N* AddNode(Args&&... args)
    {
        static_assert(std::is_base_of_v<Node, N>, "N must derive from Node");

        N* newNode = new N(std::forward<Args>(args)...);
        nodes[newNode] = {};

        newNode->transform = AddComponent<Transform2D>(newNode); //add transform component by default

        Logger::Log("New node added to the scene");
        newNode->Ready();
        return newNode;
    }

    template <typename T, typename... Args>
    T* AddComponent(Node* parentNode, Args&&... args)
    {
        // Vérifie à la compilation que T hérite de Component
        static_assert(std::is_base_of_v<Component, T>, "T must derive from Component");

        // Optionnel: Vérifier si un composant de ce type existe déjà
        // if (GetComponent<T>() != nullptr) {
        //     // Gérer le cas : retourner le composant existant, logger, ou ne rien faire
        //     return GetComponent<T>();
        // }

        T* newComponent = new T(std::forward<Args>(args)...);
        nodes[parentNode].push_back(newComponent);
        
        RenderingServer::GetInstance().UpdateComponents(GetAllComponents());

        return newComponent;
    }

    template <typename N>
    N* GetComponent(Node* parentNode)
    {
        // Vérifie à la compilation que T hérite de Component
        static_assert(std::is_base_of_v<Component, N>, "T must derive from Node");

        for (Component* comp : nodes[parentNode])
        {
            N* castedComp = dynamic_cast<N*>(comp);
            if (castedComp != nullptr)
            {
                return castedComp;
            }
        }
        return nullptr;
    }

    Node* GetRootNode(Component* comp)
    {
        for (const auto& [node, components] : nodes)
        {
            for (Component* currentComp : components)
            {
                if (currentComp == comp)
                {
                    return node;
                }
            }
        }
        return nullptr;
    }

private:
    std::map<Node*, std::vector<Component*>> nodes;
    static SceneTree* s_instance;

    std::vector<Component*> GetAllComponents()
    {
        std::vector<Component*> allComponents;
        for (const auto& [node, components] : nodes)
        {
            for (Component* component : components)
            {
                allComponents.push_back(component);
            }
        }
        return allComponents;
    }
};
