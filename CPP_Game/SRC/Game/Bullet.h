#pragma once
#include "../Engine/PhysicNode2D.h"

class Bullet : public PhysicNode2D {
public:
	Bullet(vec2 p, vec2 v, SDL_Color c, SDL_Texture* tx) {
		position = p;
		velocity = v;
		modulate = c;
		texture = tx;
	}
	~Bullet() = default;

	void Update(float deltaTime) override;
};