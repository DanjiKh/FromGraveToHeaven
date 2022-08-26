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

//----------------------------------------------------------------------------------------
// Boss   _alcohol;

// AnimatedObject player_anim;
// AnimatedObject first_punch_anim;
// AnimatedObject second_punch_anim;
// AnimatedObject third_punch_anim;

// Texture2D player_idle;
// Texture2D player_walking;
// Texture2D player_jumping;
// Texture2D player_punch;
// Texture2D player_second_punch;
// Texture2D player_third_punch;

// AnimatedObject alcohol_anim;

ObjectRoot _ground;

void InitGame()
{
	SetGameScreen();

    _player.pos = {(float)640 * 2 * 0.1f, (float)360 * 2 * 0.6f};
    _player.size = {192, 210};
    _player.vel = {0.0, 0.0};
    _player.gravity = 9.8;
    _player.speed = {200, 80};
    _player.canJump = false;
    _player.HP = 100;
    _player.damage = 20;
    _player.damage_counted = false;
    _player.attacks_count = 0;
    _player.late_ = 3.0f;

    

    // _alcohol.pos = {(float)640 * 2 * 0.8f, (float)360 * 2 * 0.6f};
    // _alcohol.size = {192, 210};
    // _alcohol.vel = {0.0, 0.0};
    // _alcohol.gravity = 9.8;
    // _alcohol.speed = {100, 35};
    // _alcohol.HP = 500;
    // _alcohol.damage = 10;
    // _alcohol.damage_counted = false;
    // _alcohol.damage_coefficient = 1280 * 0.2f;

    _ground.pos = {0, 650.0f};
    _ground.size = {640.0f*2.0f, 120.0f};

	//----------------------------------------------------------------------------------------
	// Downloading Textures
	//----------------------------------------------------------------------------------------
	

	// player_idle 		= LoadTexture("resources/Graphics/Player/Mehses/Idle/Player_idle_spriteshit.png");
	// player_idle			= GetTexture (PlayerIdleSprite);
	// player_walking  	= GetTexture (PlayerWalkingSprite);
	// player_jumping  	= GetTexture (PlayerJumpingSprite);
	// player_punch 		= GetTexture (PlayerPunchingSprite);
	// player_second_punch = GetTexture (PlayerSecondPunchSprite);
	// player_third_punch 	= GetTexture (PlayerThirdPunchSptie);
	

	//---------------------------------------------------------------------------------------
	// Creating Animated Objects
	//---------------------------------------------------------------------------------------

    // alcohol_anim.img 		  = alcohol_idle;
    // alcohol_anim.pos 		  = _alcohol.pos; 
    // alcohol_anim.frame_amount = 7;
    // alcohol_anim.FrameRec 	  = {0.0f, 0.0f, (float)alcohol_anim.img.width/(float)alcohol_anim.frame_amount, (float)alcohol_anim.img.height};
    // alcohol_anim.color        = Color {255, 255, 255, 200};
    // alcohol_anim.frameSpeed   = 0.19;

    // player_anim.img 		  = player_idle;
    // player_anim.pos 		  = _player.pos;              
    // player_anim.frame_amount  = 6;
    // player_anim.FrameRec 	  = {0.0f, 0.0f, (float)player_anim.img.width/(float)player_anim.frame_amount, (float)player_anim.img.height};
    // player_anim.color 		  = WHITE;
    // player_anim.frameSpeed 	  = 0.18;


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

void GameScreen::Draw()
{
	ClearBackground (Color {38, 36, 40});

	// ClearBackground (Color {255, 255, 255});
	
	Rectangle playerBox  = {_player.pos.x , _player.pos.y , _player.size.x , _player.size.y};
	// Rectangle alcoholBox = {_alcohol.pos.x, _alcohol.pos.y, _alcohol.size.x, _alcohol.size.y};
	Rectangle ground 	 = {_ground.pos.x , _ground.pos.y , _ground.size.x , _ground.size.y};
	
	if (CheckCollisionRecs(playerBox, ground)) {
		_player.vel.y = 0.0f;
		_player.pos.y = _ground.pos.y - _player.size.y;
		_player.canJump = true;
	} else {
		updateGravity (_player, GetFrameTime());
	}

	if (_player.canJump && IsKeyPressed(KEY_SPACE)) {
		// player_anim.isFinished = false;
		_player.isJumping = true;
		// player_anim.frameCounter = 0;
		_player.UpdateJumping (GetFrameTime());
		_player.canJump = false;
	}

	_player.SetAnimationState();

	// switch(_player.getCurrentState())
 //    {
 //        case EntityStates::IDLE:

 //            player_anim.img 		 = player_idle;	
 //            player_anim.frame_amount = 6;
 //            player_anim.frameSpeed 	 = 0.18;
 //        	player_anim.play_mode 	 = AnimatedObject::PlayMode::LOOP;
 //            break;

 //        case EntityStates::WALKING:
 //            player_anim.img 		 = player_walking;
 //            player_anim.frame_amount = 6;
 //            player_anim.frameSpeed   = 0.19;
 //        	player_anim.play_mode 	 = AnimatedObject::PlayMode::LOOP;
	// 		break;

	// 	case EntityStates::JUMPING:
	// 	 	player_anim.img 		 = player_jumping;
	// 		player_anim.frame_amount = 8;
	// 		player_anim.frameSpeed 	 = 0.07;
 //        	player_anim.play_mode	 = AnimatedObject::PlayMode::SINGLE;

 //        	if (player_anim.isFinished)
 //        		_player.isJumping = false;
	// 		break;

	// 	case EntityStates::ATTACK:
	// 		_player.DamageCalculating (_alcohol);
	// 		_player.takeDamage		  (_alcohol, CheckCollisionRecs(playerBox, alcoholBox));

	// 		combo_check (
	// 			_player,
	// 			first_punch_anim,
	// 			second_punch_anim,
	// 			third_punch_anim, 
	// 			player_punch,
	// 			player_second_punch, 
	// 			player_third_punch
	// 		);
	// 		break;
	// };

	// if (_player.attacks_count >= 1 && _player.attacks_count <= 3) {
 //        _player.delayPunch (GetFrameTime());
 //        if (_player.late_ <= 3.0f) {
 //            _player.attacks_count = 0; 
 //            _player.late_ 		  = 3.0f;
 //            _player.IsAttacking   = false;
 //        }
 //    }

 //    if (IsMouseButtonPressed (MOUSE_BUTTON_LEFT)) {
	//     _player.attacks_count++;
	//     _player.IsAttacking = true;
	//     if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && first_punch_anim.isFinished && _player.attacks_count == 1){
	//         _player.attacks_count = 2;
	//         _player.IsAttacking = true;
	//     }
	//     else if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && second_punch_anim.isFinished && _player.attacks_count == 2){
	//         _player.attacks_count = 3;
	//         _player.IsAttacking = true;
	//     }
	//     if(_player.attacks_count > 3){
	//         _player.attacks_count = 0;
	//         _player.IsAttacking = false;
	//     }
	// }

	// if (IsKeyPressed (KEY_A) || IsKeyDown (KEY_A)) {
	// 	player_anim._flip = AnimatedObject::FlipTexture::HORIZONTAL;
	// };

	// if (IsKeyPressed (KEY_D) || IsKeyDown (KEY_D)) {
	// 	player_anim._flip = AnimatedObject::FlipTexture::NONE;
	// };
	//----------------------------------------------------------------------------------------
	DrawRectangleLinesEx (playerBox, 1.0f, MAROON);
	DrawRectangleRec (ground, Color {30, 40, 255, 255});

	// if (!_player.IsAttacking) {
	// 	player_anim.Draw();
	// }
	_player._Animation.Draw(_player.pos, WHITE);

	// alcohol_anim.Draw();

	DrawText (std::to_string(float(_player.vel.y)).c_str(), 10, 50, 40, WHITE);
	//----------------------------------------------------------------------------------------
};

void UpdateGame()
{
	if (IsKeyPressed (KEY_ESCAPE) || !IsWindowFocused())
	{
			PauseGame();
			return;
	};

	_player.UpdateMoving (GetFrameTime());

	if (IsKeyPressed (KEY_A) || IsKeyDown (KEY_A)) {
		_player._Animation._flip = AnimatedSprite::FlipTexture::HORIZONTAL;
	};

	if (IsKeyPressed (KEY_D) || IsKeyDown (KEY_D)) {
		_player._Animation._flip = AnimatedSprite::FlipTexture::NONE;
	};
};