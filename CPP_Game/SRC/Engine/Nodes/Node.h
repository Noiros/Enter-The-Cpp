#pragma once

#include <glm.hpp>

enum class EntityType;

class Node
{
	public:
		using vec2 = glm::vec2;

		vec2 pos;
		vec2 vel;
		vec2 dim = {8, 8}; //width and height

		EntityType type;
		SDL_Texture* texture;
		bool toBeDestroyed = false;

		Node(vec2 p, vec2 v, EntityType t, SDL_Texture* tx) : pos(p), vel(v), type(t), texture(tx) {}
		virtual ~Node() {}

		virtual void Update(float deltaTime) = 0;
		virtual void Render(SDL_Renderer* renderer) = 0;

	private:
};

