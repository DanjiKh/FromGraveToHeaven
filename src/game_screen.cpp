#include "raylib.h"

#include "include/game_screen.hpp"

GameScreen::GameScreen (Player& player): _Player(player) {};

void GameScreen::Draw()
{
	// ClearBackground (Color {38, 36, 40});
	ClearBackground (Color {100, 100, 100, 255});

	// Rectangle alcoholBox = {_alcohol.pos.x, _alcohol.pos.y, _alcohol.size.x, _alcohol.size.y};

	// if (_player.attacks_count >= 1 && _player.attacks_count <= 3) {
 //        _player.delayPunch (GetFrameTime());
 //        if (_player.late_ <= 3.0f) {
 //            _player.attacks_count = 0; 
 //            _player.late_ 		  = 3.0f;
 //            _player.IsAttacking   = false;
 //        }
 //    }
	//----------------------------------------------------------------------------------------
	// DrawRectangleLinesEx (playerBox, 1.0f, MAROON);
	// DrawRectangleRec (ground, Color {30, 40, 255, 255});
	
	_Player._Animation.Draw(_Player.pos, GetFrameTime(), WHITE);

	DrawText (std::to_string(float(_Player.vel.y)).c_str(), 10, 50, 40, WHITE);
	//----------------------------------------------------------------------------------------
};