#pragma once
#include "Node2D.h"

class PhysicNode2D : public Node2D {
public:
	glm::vec2 velocity;

	PhysicNode2D() = default;
	virtual ~PhysicNode2D() = default;

};