#ifndef FGTH_GAMEHUD_HEADER
#define FGTH_GAMEHUD_HEADER

#include "hud.hpp"
#include "objects.hpp"

class GameScreen : public ActiveScreen
{
	public:
		GameScreen (Player& player);

		void Draw() override;

		Player& _Player;
};

#endif