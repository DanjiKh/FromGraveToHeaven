#include "raylib.h" 
#include "include/vf2d.hpp"

#include "include/game.hpp"

GameScreen _GameScreen;

void InitGame()
{
	SetActiveScreen(&_GameScreen);
};

void GameScreen::Draw()
{
	ClearBackground (Color {200, 0, 0, 255});
	
};