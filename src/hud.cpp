#include "raylib.h"

#include "include/hud.hpp"

ActiveScreen* _ActiveScreen = nullptr;

void SetActiveScreen (ActiveScreen* screen)
{
	_ActiveScreen = screen;
};

void DrawScreen()
{
	if (_ActiveScreen != nullptr)
		_ActiveScreen->Draw();
};

bool ActiveScreen::CreateBasicButton (Vector2 pos, Vector2 size, Color color, char* text, Color text_color)
{
	Rectangle b   = { pos.x, pos.y, size.x, size.y };

	bool hovered  = CheckCollisionPointRec (GetMousePosition(), b);
	bool released = IsMouseButtonReleased  (MOUSE_BUTTON_LEFT);
	bool clicked  = hovered && released;
	
	int width     = MeasureText(text, 20);

	DrawRectangle (pos.x, pos.y, size.x, size.y, color);
	DrawText 	  (text, pos.x + 20, pos.y + size.y / 2 - 10, 20, text_color);

	return clicked;

	// Button b;
	// b.box   	 = { pos.x(), pos.y(), size.x(), size.y() };
	// b.color 	 = color;
	// b.text  	 = text;
	// b.text_color = text_color;

	// _aButtons.push_back(b);
};