#pragma once

#include <vector>

#include "Node.h"

class SceneTree
{
    public:
        void UpdateNodes(SDL_Renderer* renderer, float deltaTime);
    
        template <class N, class ... Args>
        N* AddNode(Args&&... args)
        {    
            // Vérifie à la compilation que T hérite de Component
            static_assert(std::is_base_of<Node, N>::value, "N must derive from Node");

            // Optionnel: Vérifier si un composant de ce type existe déjà
            // if (GetComponent<T>() != nullptr) {
            //     // Gérer le cas : retourner le composant existant, logger, ou ne rien faire
            //     return GetComponent<T>();
            // }

            N* newNode = new N(std::forward<Args>(args)...);
            nodes.push_back(newNode);
            newNode->Ready();
            return newNode;
        }

        template<typename T, typename... Args>
        T* AddComponent(Node* parentNode, Args&&... args)
        {    
            // Vérifie à la compilation que T hérite de Component
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            // Optionnel: Vérifier si un composant de ce type existe déjà
            // if (GetComponent<T>() != nullptr) {
            //     // Gérer le cas : retourner le composant existant, logger, ou ne rien faire
            //     return GetComponent<T>();
            // }

            T* newComponent = new T(std::forward<Args>(args)...);
            newComponent->ParentNode = parentNode;
            components.push_back(newComponent);
            return newComponent;
        }

        std::vector<Node*> nodes;
        std::vector<Component*> components;
};
