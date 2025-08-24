#pragma once
#include <array>
#include <bitset>

class GameObject;
class Component;

using ComponentTypeID = std::size_t;

inline ComponentTypeID GetUniqueComponentID()
{
    static ComponentTypeID lastID = 0u;
    return lastID++;
}

template<typename T>
inline ComponentTypeID GetComponentTypeID() noexcept
{
    static_assert(std::is_base_of<Component, T>::value, "T must be a Component");
    static const ComponentTypeID typeID = GetUniqueComponentID();
    return typeID;
}

constexpr std::size_t MAX_GAMEOBJECTS = 5000;
constexpr std::size_t MAX_COMPONENTS = 32;

using ComponentBitset = std::bitset<MAX_COMPONENTS>;
using ComponentArray = std::array<Component*, MAX_COMPONENTS>;


