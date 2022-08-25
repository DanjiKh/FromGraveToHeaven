#include "raylib.h"
#include "include/objects.hpp"

Player::Player()
{
	_currentstate = EntityStates::IDLE;
}

void Player::setState (EntityStates newState)
{
	_currentstate = newState;
}

void Player::UpdateMoving (float delT)
{
	vel.x = 0.0f;

	if (IsKeyDown (KEY_D)) {
		vel.x += 1.0f;
	}
	if (IsKeyDown (KEY_A)) {
		vel.x += -1.0f;
	}

	pos.x += vel.x * speed.x * delT;
};

void Player::UpdateJumping (float delT)
{
	auto p0 = pos.y - 150;
	while (pos.y >= p0)
	{
		pos.y += vel.y * speed.y * delT;
		vel.y += -1.0f * speed.y * delT;

		if(pos.y == p0)
			vel.y = 0.0f;
	}
};

void Player::SetAnimationState()
{
	if ((IsKeyDown (KEY_D) || IsKeyDown (KEY_A)) && !isJumping) {
		setState(EntityStates::WALKING);
	} else if (isJumping) {
		setState(EntityStates::JUMPING);
	} else if (IsAttacking) {
		setState(EntityStates::ATTACK);
	} else {
		setState(EntityStates::IDLE);
	}
};

void Player::delayPunch (float delT)
{
	if (IsTimerActive)
		late_ -= delT;
};

void updateGravity(DynamicObject& a, float delT)
{
	a.pos.y += a.vel.y * a.speed.y * delT;
	a.vel.y += 1.0f * a.speed.y * delT;
};

