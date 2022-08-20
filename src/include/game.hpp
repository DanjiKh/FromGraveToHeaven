#ifndef FGTH_GAMEHUD_HEADER
#define FGTH_GAMEHUD_HEADER

#include "hud.hpp"

void InitGame     ();
void SetGameScreen();

class GameScreen : public ActiveScreen
{
	public:
		void Draw() override;
};

#endif