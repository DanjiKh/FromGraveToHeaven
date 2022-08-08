#ifndef FGTH_HUD_HEADER
#define FGTH_HUD_HEADER

#include "iostream"

#include "raylib.h"
#include "vf2d.hpp"

// struct Button
// {
// 	Rectangle box;
// 	Color     color;
// 	char*  	  text;
// 	Color     text_color;
// 	bool      isCliked;
// };

// Basic class for game screens
//----------------------------------------------------------------------------------------
class ActiveScreen
{
	public:
		virtual void Draw() = 0;

	protected:
		bool CreateBasicButton (vf2d pos, vf2d size, Color color, char* text, Color text_color);
		// void DrawButtons    ();
};
//----------------------------------------------------------------------------------------

void SetActiveScreen (ActiveScreen* screen);

void DrawScreen		 ();

#endif