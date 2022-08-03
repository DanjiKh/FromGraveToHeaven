#ifndef FGTH_HUD_HEADER
#define FGTH_HUD_HEADER

#include "iostream"

#include "raylib.h"
#include "vf2d.hpp"

// ==========================================
struct Button
{	
	vf2d  		pos;
	vf2d  		size;
	Color 		color;
	char*		text;
	Color 		text_color;
};
// ==========================================

//----------------------------------------------------------------------------------------
class ActiveScreen
{
	public:
		virtual void Draw() = 0;

	protected:
		void CreateBasicButton  (vf2d pos, vf2d size, Color color, char* text, Color text_color);
		// void DrawButtons   		();

	
	protected:
		std::vector<Button> _aButtons;
};
//----------------------------------------------------------------------------------------

void SetActiveScreen (ActiveScreen* screen);

void DrawScreen();

#endif