#include "raylib.h"

#include "include/game_screen.hpp"

GameScreen::GameScreen (Player& player): _Player(player) {};

void GameScreen::Draw()
{
	ClearBackground (Color {38, 36, 40});

	// Rectangle alcoholBox = {_alcohol.pos.x, _alcohol.pos.y, _alcohol.size.x, _alcohol.size.y};

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
	// DrawRectangleLinesEx (playerBox, 1.0f, MAROON);
	// DrawRectangleRec (ground, Color {30, 40, 255, 255});

	// if (!_player.IsAttacking) {
	// 	player_anim.Draw();
	// }
	_Player._Animation.Draw(_Player.pos, WHITE);

	DrawText (std::to_string(float(_Player.vel.y)).c_str(), 10, 50, 40, WHITE);
	//----------------------------------------------------------------------------------------
};