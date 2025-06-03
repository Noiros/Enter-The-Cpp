#pragma once

#include <vector>
#include <memory>
#include <string>
#include "../ECS/ECS.h"
#include "Component.h"
#include "../Engine/Components/Transform2D.h"

class GameObject
{
public:
    GameObject()
    {
        transform = &this->AddComponent<Transform2D>();
    };
    virtual ~GameObject() = default;

    template<typename T, typename... TArgs>
    inline T& AddComponent(TArgs&&... args)
    {
        T* comp = new T(std::forward<TArgs>(args)...);
        std::unique_ptr<Component> uptr {comp};
        comp->gameObject = this;

        components.emplace_back(std::move(uptr));
        compBitset[GetComponentTypeID<T>()] = true;
        compList[GetComponentTypeID<T>()] = comp;
        comp->Ready();
        return *comp;
    }

    template<typename T>
    inline T& GetComponent()
    {
        auto ptr = compList[GetComponentTypeID<T>()];
        return *static_cast<T*>(ptr);
    }

    inline std::vector<std::unique_ptr<Component>>* GetAllComponents()
    {
        return &components;
    }

    template<typename T>
    inline bool HasComponent()
    {
        return compBitset[GetComponentTypeID<T>()];
    }

    inline bool IsActive() const
    {
        return active;
    }

    inline std::string GetName() const
    {
        return name;
    }

    inline void SetName(std::string_view name)
    {
        this->name = name;
    }

    inline void DestroyGameObject()
    {
        active = false;
    }

    Transform2D* transform;
    virtual void Ready() {
        active = true;
    }
    virtual void Update(float deltaTime) {}
    virtual void Render(SDL_Renderer* renderer, glm::vec2 cameraPos, float cameraScale) {}
    
    
private:
    std::string name;
    bool active = false;
    ComponentArray compList;
    ComponentBitset compBitset;
    std::vector<std::unique_ptr<Component>> components;
};
