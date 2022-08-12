#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/game.hpp"
#include "include/objects.hpp"

GameScreen _GameScreen;

Player _player;

Boss _alcohol;

AnimatedObject alcohol_anim;
AnimatedObject player_anim;

void InitGame()
{
	SetActiveScreen(&_GameScreen);

    _player.pos = {(float)640 * 2 * 0.1f, (float)360 * 2 * 0.6f};
    _player.size = {64, 64};
    _player.vel = {0.0, 0.0};
    _player.gravity = 9.8;
    _player.speed = {100, 35};
    _player.jump = true;
    _player.HP = 100;
    _player.damage = 20;
    _player.damage_counted = false;

    _alcohol.pos = {(float)640 * 2 * 0.8f, (float)360 * 2 * 0.6f};
    _alcohol.size = {64, 64};
    _alcohol.vel = {0.0, 0.0};
    _alcohol.gravity = 9.8;
    _alcohol.speed = {100, 35};
    _alcohol.HP = 500;
    _alcohol.damage = 10;
    _alcohol.damage_counted = false;

	//----------------------------------------------------------------------------------------
	// Downloading Textures
	//----------------------------------------------------------------------------------------
	Texture2D player_idle 	  = LoadTexture("resources/Graphics/Player/Mehses/Idle/Player_idle_spriteshit.png");
	Texture2D player_walking  = LoadTexture("resources/Graphics/Player/Mehses/Walking/Player_walking_spriteshit.png");
	Texture2D alcohol_idle 	  = LoadTexture("resources/Graphics/Boss/Meshes/1st_boss_standing_spriteshit.png");
	Texture2D alcohol_walking = LoadTexture("resources/Graphics/Boss/Meshes/1st_boss_walking_spriteshit.png");	
	    
	//---------------------------------------------------------------------------------------
	// Creating Animated Objects
	//---------------------------------------------------------------------------------------

    
    
    alcohol_anim.title = "IDLE";
    alcohol_anim.img = alcohol_idle;
    alcohol_anim.pos = _alcohol.pos; 
    alcohol_anim.frame_amount = 7;
    alcohol_anim.FrameRec = {0.0f, 0.0f, (float)alcohol_anim.img.width/(float)alcohol_anim.frame_amount, (float)alcohol_anim.img.height};
    alcohol_anim.color = WHITE;
    alcohol_anim.frameSpeed = 6;

    player_anim.title = "IDLE";
    player_anim.img = player_idle;
    player_anim.pos = _player.pos;                
    player_anim.frame_amount = 6;
    player_anim.FrameRec = {0.0f, 0.0f, -(float)player_anim.img.width/(float)player_anim.frame_amount, (float)player_anim.img.height};
    player_anim.color = WHITE;
    player_anim.frameSpeed = 9;
};

void GameScreen::Draw()
{
	ClearBackground (Color {200, 0, 0, 255});
	//updateInputs();

	alcohol_anim.DrawAnimatedObject();
	player_anim.DrawAnimatedObject();
};