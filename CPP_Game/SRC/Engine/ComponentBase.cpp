#pragma once

class Component
{
public:
    virtual ~Component() = default; // Destructeur virtuel pour permettre dynamic_cast
};