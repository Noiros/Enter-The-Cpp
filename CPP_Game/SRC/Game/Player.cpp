#include "Player.h"
#include "Game.h"

void Player::Update(float deltaTime) {
	const float rightBorder = DISPLAY_WIDTH - size.x;
	const float bottomBorder = DISPLAY_HEIGHT - size.y;

	position += velocity * deltaTime;

	if (position.x >= rightBorder) {
		position.x = rightBorder - (position.x - rightBorder);
		velocity.x = -velocity.x;
	}
	else if (position.x <= 0)
	{
		position.x = -position.x;
		velocity.x = -velocity.x;
	}

	if (position.y >= bottomBorder) {
		position.y = bottomBorder - (position.y - bottomBorder);
		velocity.y = -velocity.y;
	}
	else if (position.y <= 0)
	{
		position.y = -position.y;
		velocity.y = -velocity.y;
	}
}