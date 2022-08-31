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
	_Animation.addAnimation ("jumping", PlayerJumpingSprite, 8, 0.13f, AnimatedSprite::PlayMode::SINGLE);

	_Animation.addAnimation ("punch", PlayerPunchingSprite, 10, 0.09f, AnimatedSprite::PlayMode::SINGLE);
	_Animation.addAnimation ("second_punch", PlayerSecondPunchSprite, 10, 0.1f, AnimatedSprite::PlayMode::SINGLE);
	_Animation.addAnimation ("third_punch", PlayerThirdPunchSprite, 15, 0.08f, AnimatedSprite::PlayMode::SINGLE);

	_Animation.setAnimation ("idle");
};

void Player::setState (EntityStates newState)
{
	_currentstate = newState;
};

void Player::checkState()
{
	if (isAttacking) {
		setState (EntityStates::ATTACK);
	} else if (isJumping) {
		setState (EntityStates::JUMPING);
	} else if ((IsKeyDown (KEY_D) || IsKeyDown (KEY_A))) {
		setState (EntityStates::WALKING);
	} else {
		setState (EntityStates::IDLE);
	}
};

void Player::checkCurrentAnimation()
{
	switch (getCurrentState())
	{
		case EntityStates::IDLE:
			_Animation.setAnimation ("idle");
			break;

		case EntityStates::WALKING:
			_Animation.setAnimation ("walking");
			break;

		case EntityStates::JUMPING:
			_Animation.setAnimation ("jumping");
			if (_Animation.frameCounter == 0)
			{
				_Animation.frameCounter = 2;
			}
			break;

		case EntityStates::ATTACK:
			switch (attacks_count)
			{
				case 1:
					_Animation.setAnimation ("punch");
					break;

				case 2:
					_Animation.setAnimation ("second_punch");
					break;

				case 3:
					_Animation.setAnimation ("third_punch");
					break;
			}
			break;
	};
};

void Player::setAnimationFlip()
{
	if (IsKeyPressed (KEY_A) || IsKeyDown (KEY_A)) {
		_Animation._flip = AnimatedSprite::FlipTexture::HORIZONTAL;
	};

	if (IsKeyPressed (KEY_D) || IsKeyDown (KEY_D)) {
		_Animation._flip = AnimatedSprite::FlipTexture::NONE;
	};
};

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

void Player::delayPunch (float delT)
{
	if (IsTimerActive)
		late_ -= delT;
};

void Player::checkCombo()
{
	switch (attacks_count)
	{
		case 1:
			if (!_Animation.isFinished) {
				IsTimerActive = false;
			} else {
				IsTimerActive = true;
				
				if (late_ <= 0.0f) {
                	IsTimerActive = false;
					isAttacking = false;
				}
			}
			break;

		case 2:
			if (!_Animation.isFinished) {
				IsTimerActive = false;
			} else {
				IsTimerActive = true;

				if (late_ <= 0.0f) {
                	IsTimerActive = false;
					isAttacking = false;
				}
			}
			break;

		case 3:
			if (!_Animation.isFinished) {
				IsTimerActive = false;
			} else {
				IsTimerActive = true;
                
                if (late_ <= 0.0f) {
                	IsTimerActive = false;
					isAttacking = false;
				}								
			}
			break;
	};	
};

void updateGravity (DynamicObject& a, float delT)
{
	a.pos.y += a.vel.y * a.speed.y * delT;
	a.vel.y += 1.0f * a.speed.y * delT;
};