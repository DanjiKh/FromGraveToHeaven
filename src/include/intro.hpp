#pragma once

#include "raylib.h"

#include "main.hpp"
// #include "vf2d.hpp"

void DrawTitle (float fTime) 
{ 
	// TODO: Add fonts

	int _textwidth = MeasureText (_NameOfApplicatoin, 20);
    DrawText (_NameOfApplicatoin, GetScreenWidth() / 2 - _textwidth / 2, GetScreenHeight() / 2 - 10, 20, Color {255, 255, 255, static_cast<unsigned char>(_DeltaFade)});          

			
	// Copyright
	// DrawString (ScreenWidth() - GetTextSize("Copyright {team name} 2022 ").x - 5, ScreenHeight() - GetTextSize("Copyright {team name} 2022").y - 5, "Copyright Danilo Khvorost 2022", olc::Pixel(255, 255, 255));
}

bool UpdateIntro (float fTime)
{
	// TODO: Make a more interesing intro

    if (_TimeAccumilator < 3.0f) {
       	_DeltaFade += fTime * 200.0f;
       	if (_DeltaFade > 255.0f) _DeltaFade = 255.0f;
    }

    if (_TimeAccumilator > 3.0f) {
       	_DeltaFade -= fTime * 200.0f;
       	if (_DeltaFade < 0.1f) _DeltaFade = 0.0f;
    }      

    return true;
}