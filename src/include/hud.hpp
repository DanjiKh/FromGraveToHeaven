#ifndef FGTH_HUD_HEADER
#define FGTH_HUD_HEADER

#include "raylib.h"

class ActiveScreen
{
	public:
		virtual void Draw();
		virtual void Update();

protected:
	

};

class Menu : public ActiveScreen
{
	public:


}


#endif