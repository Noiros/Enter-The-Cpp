#pragma once

#include "Component.h" // Inclure la définition de Component
#include "Components/Transform.h" // On suppose que Transform hérite de Component

#include <vector>
#include <typeinfo> // Pour dynamic_cast
#include <memory>   // Pour std::is_base_of, std::forward (bien que forward soit dans <utility>)
#include <utility>  // Pour std::forward

// Forward declarations si nécessaires
struct SDL_Renderer;
enum class EntityType; // Conserve la déclaration si elle est utilisée ailleurs

class Node
{
    public:
        // Transform transform; // Remplacé par une collection de composants ci-dessous
        std::vector<Component*> m_components; // Collection pour stocker les composants
        bool toBeDestroyed = false;
        Transform* transform;

        virtual ~Node()
        {
            // Nettoyer les composants si Node en est propriétaire
            for (Component* comp : m_components)
            {
                delete comp;
            }
            m_components.clear();
        }
        
        /**
         * @brief Récupère le premier composant du type T attaché à ce Node.
         * @tparam T Le type du composant à récupérer (doit hériter de Component).
         * @return Un pointeur vers le composant de type T s'il est trouvé, sinon nullptr.
         */
        template<typename T>
        T* GetComponent()
        {
            // Vérifie à la compilation que T hérite de Component
            static_assert(std::is_base_of<Component, T>::value, "T must derive from Component");

            for (Component* comp : m_components)
            {
                T* castedComp = dynamic_cast<T*>(comp);
                if (castedComp != nullptr)
                {
                    return castedComp;
                }
            }
            return nullptr;
        }
        
        // L'ancienne déclaration `virtual Component GetComponent() = 0;` est supprimée car elle
        // n'est pas adaptée pour retourner des types de composants spécifiques.

        virtual void Ready() = 0;
        virtual void Update(float deltaTime) = 0;
};
