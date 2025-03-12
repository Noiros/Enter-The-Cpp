#pragma once
#include "../Engine/PhysicNode2D.h"

class Player : public PhysicNode2D {
public:
	Player(vec2 p, vec2 v, SDL_Color c, SDL_Texture* tx) {
		position = p;
		velocity = v;
		modulate = c;
		texture = tx;
	}
	~Player() = default;

	void Update(float deltaTime) override;
};