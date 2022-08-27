#include "raylib.h"

#include "include/main.hpp"
#include "include/hud.hpp"
#include "include/game.hpp"
#include "include/game_screen.hpp"
#include "include/objects.hpp"
#include "include/animated_sprites.hpp"
#include "include/resources_loading.hpp"
#include "include/resources_ids.hpp"

#include <cmath>

Player _player;

GameScreen _GameScreen(_player);

ObjectRoot _ground;

void InitGame()
{
	SetGameScreen();

    // _alcohol.pos = {(float)640 * 2 * 0.8f, (float)360 * 2 * 0.6f};
    // _alcohol.size = {192, 210};
    // _alcohol.vel = {0.0, 0.0};
    // _alcohol.gravity = 9.8;
    // _alcohol.speed = {100, 35};
    // _alcohol.HP = 500;
    // _alcohol.damage = 10;
    // _alcohol.damage_counted = false;
    // _alcohol.damage_coefficient = 1280 * 0.2f;

    _ground.pos = { 0, 650.0f };
	_ground.size = { 640.0f*2.0f, 120.0f };

	//---------------------------------------------------------------------------------------
	// Creating Animated Objects
	//---------------------------------------------------------------------------------------

    // alcohol_anim.img 		  = alcohol_idle;
    // alcohol_anim.pos 		  = _alcohol.pos; 
    // alcohol_anim.frame_amount = 7;
    // alcohol_anim.FrameRec 	  = {0.0f, 0.0f, (float)alcohol_anim.img.width/(float)alcohol_anim.frame_amount, (float)alcohol_anim.img.height};
    // alcohol_anim.color        = Color {255, 255, 255, 200};
    // alcohol_anim.frameSpeed   = 0.19;

    // first_punch_anim.img = player_punch;
    // first_punch_anim.pos = _player.pos; 
    // first_punch_anim.frame_amount = 10;
    // first_punch_anim.FrameRec = {0.0f, 0.0f, (float)first_punch_anim.img.width/(float)first_punch_anim.frame_amount, (float)first_punch_anim.img.height};
    // first_punch_anim.color = WHITE;
    // first_punch_anim.frameSpeed = 0.1;

    // second_punch_anim.img = player_second_punch;
    // second_punch_anim.pos = _player.pos; 
    // second_punch_anim.frame_amount = 10;
    // second_punch_anim.FrameRec = {0.0f, 0.0f, (float)second_punch_anim.img.width/(float)second_punch_anim.frame_amount, (float)second_punch_anim.img.height};
    // second_punch_anim.color = WHITE;
    // second_punch_anim.frameSpeed = 0.1;

    // third_punch_anim.img = player_third_punch;
    // third_punch_anim.pos = _player.pos; 
    // third_punch_anim.frame_amount = 13;
    // third_punch_anim.FrameRec = {0.0f, 0.0f, (float)third_punch_anim.img.width/(float)third_punch_anim.frame_amount, (float)third_punch_anim.img.height};
    // third_punch_anim.color = WHITE;
    // third_punch_anim.frameSpeed = 0.1;
};

void SetGameScreen()
{
	SetActiveScreen (&_GameScreen);
};

void checkPlayerAnimation()
{
	switch(_player.getCurrentState())
	{
		case EntityStates::IDLE:
			_player._Animation.setAnimation ("idle");
			break;

		case EntityStates::WALKING:
			_player._Animation.setAnimation ("walking");
			break;

		case EntityStates::JUMPING:
			_player._Animation.setAnimation ("jumping");
			break;
	};
};

void UpdateGame()
{
	if (IsKeyPressed (KEY_ESCAPE) || !IsWindowFocused())
	{
			PauseGame();
			return;
	};

	Rectangle playerBox  = {_player.pos.x , _player.pos.y , _player.size.x , _player.size.y};
	Rectangle ground = {_ground.pos.x , _ground.pos.y , _ground.size.x , _ground.size.y};

	_player.UpdateMoving (GetFrameTime());

	if (CheckCollisionRecs(playerBox, ground)) {
		_player.vel.y = 0.0f;
		_player.canJump = true;
		_player.pos.y = _ground.pos.y - _player.size.y;
	} else {
		updateGravity (_player, GetFrameTime());
	}

	if (_player.canJump && IsKeyPressed(KEY_SPACE)) {
		_player.isJumping = true;
		_player.UpdateJumping (GetFrameTime());
		_player.canJump = false;
	}

	if (_player.getCurrentState() == EntityStates::JUMPING && _player._Animation.isFinished) {
		_player.isJumping = false;
	}

	_player.checkState();
	checkPlayerAnimation();
	
	if (IsKeyPressed (KEY_A) || IsKeyDown (KEY_A)) {
		_player._Animation._flip = AnimatedSprite::FlipTexture::HORIZONTAL;
	};

	if (IsKeyPressed (KEY_D) || IsKeyDown (KEY_D)) {
		_player._Animation._flip = AnimatedSprite::FlipTexture::NONE;
	};
};