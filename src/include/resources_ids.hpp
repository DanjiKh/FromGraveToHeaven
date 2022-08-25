#pragma once

#include "raylib.h"

constexpr int PlayerIdleSprite 	  		= 0;
constexpr int PlayerWalkingSprite		= 1;
constexpr int PlayerJumpingSprite 		= 2;
constexpr int PlayerPunchingSprite  	= 3;
constexpr int PlayerSecondPunchSprite 	= 4;
constexpr int PlayerThirdPunchSptie 	= 5;

const Texture& GetTexture (int id);