#include "raylib.h"
#include "vf2d.hpp"

#include "hud.hpp"

void InitGame();

class GameScreen : public ActiveScreen
{
	public:
		void Draw() override;
};