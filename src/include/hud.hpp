#ifndef FGTH_HUD_HEADER
#define FGTH_HUD_HEADER

#include "iostream"

#include "raylib.h"

// Basic class for game screens
//----------------------------------------------------------------------------------------
class ActiveScreen
{
	public:
		virtual void Draw() = 0;

	protected:
		bool CreateBasicButton (Vector2 pos, Vector2 size, Color color, std::string text, Color text_color);
};
//----------------------------------------------------------------------------------------

void SetActiveScreen (ActiveScreen* screen);

void DrawScreen ();

#endif