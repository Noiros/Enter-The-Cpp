#pragma once

#include <map>
#include <vector>

#include "../Node.h"
#include "../Component.h"
#include "../Components/Transform.h"

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

        newNode->transform = AddComponent<Transform>(newNode); //add transform component by default

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
        //newComponent->ParentNode = parentNode;
        nodes[parentNode].push_back(newComponent);
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
}; // Ajout du point-virgule ici
