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
ObjectRoot _ground;

GameScreen _GameScreen(_player);

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
};

void SetGameScreen()
{
	SetActiveScreen (&_GameScreen);
};

void UpdatePlayer() {
	Rectangle playerBox  = {_player.pos.x , _player.pos.y , _player.size.x , _player.size.y};
	Rectangle ground = {_ground.pos.x , _ground.pos.y , _ground.size.x , _ground.size.y};
	
	_player.checkState();

	// Gravity
	//----------------------------------------------------------------------------------------
	if (CheckCollisionRecs (playerBox, ground)) {
		_player.vel.y     = 0.0f; // TODO: make a function for resolve collisions
		_player.canJump   = true;
		_player.isJumping = false; // Finishing all updates for jump
	} else {
		updateGravity (_player, GetFrameTime());
	}
	//----------------------------------------------------------------------------------------

	if (_player.getCurrentState() != EntityStates::ATTACK) {
		_player.UpdateMoving (GetFrameTime());
	}

	// Jump
	//----------------------------------------------------------------------------------------
	if (_player.canJump && IsKeyPressed (KEY_SPACE) && !_player.isAttacking){
		_player.isJumping = true;
		_player.UpdateJumping (GetFrameTime());
		_player.canJump = false;
	}
	//----------------------------------------------------------------------------------------

	// Attacks
	//----------------------------------------------------------------------------------------
	if (!_player.isAttacking) { 
		_player.attacks_count = 0;
		_player.late_ = 0.5f;
	}

	// if (_player.attacks_count == 3) {
	// 	_player.attacks_count = 0;
	// 	_player.late_ = 0.5f;
	// }

	if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) && !_player.isAttacking && !_player.isJumping) {
		_player.isAttacking = true;
		_player.attacks_count++;
		_player.late_ = 0.5f;
	}

	if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT) && _player.IsTimerActive && _player.attacks_count <= 2) {
		_player.attacks_count++;
		_player.late_ = 0.5f;
	}

	if (_player.attacks_count == 3 && _player.canJump && _player._Animation.frameCounter == 6) {
		_player.UpdateJumping (GetFrameTime());
		_player.canJump = false;
	}
	
	_player.delayPunch (GetFrameTime());
	_player.checkCombo();
	//----------------------------------------------------------------------------------------

	_player.checkCurrentAnimation();
	if (_player.getCurrentState() != EntityStates::ATTACK && 
		 _player.getCurrentState() != EntityStates::JUMPING) {
		_player.setAnimationFlip();
	}
};

void UpdateGame()
{
	if (IsKeyPressed (KEY_ESCAPE)/* || !IsWindowFocused()*/)
	{
		// PauseGame();
		QuitApplication();
		return;
	};

	UpdatePlayer();


};