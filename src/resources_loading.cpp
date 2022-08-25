#include "raylib.h"
#include "raymath.h"

#include "include/resources_loading.hpp"
#include "include/resources_ids.hpp"
#include "include/main.hpp"
#include "include/hud.hpp"

#include <string>
#include <vector>
#include <deque>

class LoadingScreen : public ActiveScreen
{
	public:
		LoadingScreen()
		{
			int size = MeasureText(LoadingText.c_str(), 20);
		};

		void Draw() override
		{
			// TODO: ADD loading animation;
			//----------------------------------------------------------------------------------------
		};

		std::string LoadingText = "Loading...";
		float Progress = 0.0f;
};

LoadingScreen* _LoadingScreen = nullptr;

std::deque  <std::string> TexturesToLoad;
std::vector <Texture> 	  LoadedTextures;

Texture DefaultTexture = { 0 };

size_t LoadedItems = 0;
size_t TotalToLoad = 0;

void InitResources()
{
	_LoadingScreen = new LoadingScreen();
	SetActiveScreen (_LoadingScreen);

	// Player Idle
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Idle/Player_idle_spriteshit.png");
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Walking/Player_walking_spriteshit.png");
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Jumping/Jump/Player_Jumping_spriteshit1.png");
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Attacks/First Punch/Player_first_punch_spriteshit.png");
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Attacks/Second Punch/Player_second_punch_spriteshit.png");
	TexturesToLoad.emplace_back("resources/Graphics/Player/Mehses/Attacks/Third Punch/Player_third_punch.spriteshit.png");

	TotalToLoad = TexturesToLoad.size();
};

void CleanupResources()
{
	if (_LoadingScreen != nullptr)
		delete(_LoadingScreen);

	UnloadTexture (DefaultTexture);
	for (const Texture& texture : LoadedTextures)
		UnloadTexture (texture);

	LoadedTextures.clear();
	DefaultTexture.id = 0;
	_LoadingScreen = nullptr;
};

void UpdateLoad()
{
	if (TexturesToLoad.empty()) {
		StartIntro();
		return;
	};

	const int maxToLoadPerFrame = 1;

	for (int i = 0; i < maxToLoadPerFrame; ++i) {
		if (!TexturesToLoad.empty()) {
			LoadedTextures.push_back (LoadTexture (TexturesToLoad.front().c_str()));
			TexturesToLoad.pop_front();

			LoadedItems++;
		}
	};

	_LoadingScreen->Progress = LoadedItems / float(TotalToLoad);
};

const Texture& GetTexture (int id)
{
	if (id < 0 || id > int(LoadedTextures.size()))
		return DefaultTexture;

	return LoadedTextures[id];
};

