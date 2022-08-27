#include "raylib.h"
#include "include/objects.hpp"
#include "include/animated_sprites.hpp"
#include "include/resources_ids.hpp"

Player::Player()
{
	pos   = Vector2 {0.0f, 0.0f};
	size  = Vector2 {192.0f, 210.0f};
	vel   = Vector2 {0.0f, 0.0f};
	speed = Vector2 {200.0f, 80.0f};
	gravity = 9.8f;
	canJump = false;
	HP = 100.0f;
   	damage = 20.0f;
   	damage_counted = false;
   	attacks_count = 0;
   	late_ = 3.0f;

	_currentstate = EntityStates::IDLE;

	_Animation.addAnimation ("idle", PlayerIdleSprite, 6, 0.18f, AnimatedSprite::PlayMode::LOOP);
	_Animation.addAnimation ("walking", PlayerWalkingSprite, 6, 0.19f, AnimatedSprite::PlayMode::LOOP);
	_Animation.addAnimation ("jumping", PlayerJumpingSprite, 8, 0.08f, AnimatedSprite::PlayMode::SINGLE);

	_Animation.setAnimation ("idle");
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
	auto p0 = pos.y - 100;
	while (pos.y >= p0)
	{
		pos.y += vel.y * speed.y * delT;
		vel.y += -1.0f * speed.y * delT;

		if(pos.y == p0)
			vel.y = 0.0f;
	}
};

void Player::checkState()
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

