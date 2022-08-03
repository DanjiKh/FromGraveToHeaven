#pragma once

#include "raylib.h"

#include "main.hpp"
#include "vf2d.hpp"

float _DeltaFade;

int _TitleFontSize;

Font _8_bit_Limit;

void DrawTitle (float fTime) 
{ 
	// TODO: Add fonts

	// int _textwidth = MeasureText (_NameOfApplicatoin, _TitleFontSize);
    // DrawText (_NameOfApplicatoin, GetScreenWidth() / 2 - _textwidth / 2, GetScreenHeight() / 2 - 10, _TitleFontSize, Color {255, 255, 255, static_cast<unsigned char>(_DeltaFade)});          
	
	Vector2 _Vtextwidth = MeasureTextEx (_8_bit_Limit, _NameOfApplicatoin, _TitleFontSize, 15);
	Vector2 title_pos 	= Vector2 {(float)(GetScreenWidth() / 2 - _Vtextwidth.x / 2), (float)(GetScreenHeight() / 2 - _Vtextwidth.y / 2)};
	DrawTextEx (_8_bit_Limit, _NameOfApplicatoin, title_pos, _TitleFontSize, 15, Color {255, 255, 255, static_cast<unsigned char>(_DeltaFade)});
	
	// Copyright
	int _textwidth = MeasureText (_CopyrightString, 20);
	DrawText (_CopyrightString, GetScreenWidth() - _textwidth - 5, GetScreenHeight() - 20, 20, Color {255, 255, 255, static_cast<unsigned char>(_DeltaFade)}); 
};

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