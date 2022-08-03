#include "raylib.h"
#include "include/vf2d.hpp"

#include "include/hud.hpp"

ActiveScreen* _ActiveScreen = nullptr;

void SetActiveScreen(ActiveScreen* screen)
{
	_ActiveScreen = screen;
};

void DrawScreen()
{
	if (_ActiveScreen != nullptr)
		_ActiveScreen->Draw();
};

void ActiveScreen::CreateBasicButton (vf2d pos, vf2d size, Color color, char* text, Color text_color)
{
	int width = MeasureText(text, 20);
	DrawRectangle (pos.x(), pos.y(), size.x(), size.y(), color);
	DrawText 	  (text, pos.x() + 20, pos.y() + size.y() / 2 - 10, 20, text_color);


	// Button b;
	// b.pos 		 = pos;
	// b.size 		 = size;
	// b.color 	 = color;
	// b.text 		 = text;
	// b.text_color = text_color;
	// _aButtons.push_back(b);
};