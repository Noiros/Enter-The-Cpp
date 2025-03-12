#pragma once
#include "Node.h"
#include <glm.hpp>
#include <SDL.h>


class Node2D : public Node {
public:
	using vec2 = glm::vec2;

	vec2 position;
	vec2 scale = vec2(1, 1);
	float rotation;

	SDL_Color modulate;
	SDL_Texture* texture;
	vec2 size = { 8, 8 }; //sprite width and height

	Node2D() = default;
	virtual ~Node2D() = default;
};