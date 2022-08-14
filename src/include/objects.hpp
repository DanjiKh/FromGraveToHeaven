#ifndef FGTH_OBJECTS_HEADER
#define FGTH_OBJECTS_HEADER

#include <iostream>
#include <string>
#include <cmath>

#include "raylib.h"

//----------------------------------------------------------------------------------------
enum class AnimationState
{
	IDLE 		, WALKING, 
	JUMPING		, 
	ATTACK      , COMBO
} _AnimationState;
//----------------------------------------------------------------------------------------

class ObjectRoot
{
	public:
		Vector2  pos;
		Vector2  size;
};

/*
	+----------------------------------------------+
	|          Branch for dynamic objects          |			
	+----------------------------------------------+
*/
class DynamicObject: public ObjectRoot
{
	public:
		Vector2 vel;
		float 	gravity;
};

class Player : public DynamicObject
{
	public:
		Vector2 speed;
		bool  	jump;
		float 	HP;
		float 	damage;
		bool  	damage_counted;
	public:
		void UpdateInputs(float delT)
		{
			vel.x = 0.0f;

			if (IsKeyDown (KEY_A)) {
				vel.x += -1.0f;
			}
			if (IsKeyDown (KEY_D)) {
				vel.x += 1.0f;
			}

			// pos += vel * Vector2 (200.0f, 35.0f) * delT;
			pos.x += vel.x * 200.0f * delT;
		}
};

class Boss : public DynamicObject
{
	public:
		Vector2 speed;
		float 	HP;
		float 	damage;
		bool  	damage_counted;
};

class AnimatedObject : public ObjectRoot
{
	public:
		Texture2D 	img;
		Vector2   	pos;
		int       	frame_amount;
		Rectangle 	FrameRec;
		Color 		color;
		int 		frameSpeed;

	private:
		int currentFrame = 0;
		int frameCounter = 0;

	public:
		void DrawAnimatedObject()
		{
			frameCounter++;

			if (frameCounter >= (60 / frameSpeed)) {
				frameCounter = 0;
				currentFrame++;

				if (currentFrame > frame_amount)
					currentFrame = 0;
				FrameRec.x = (float)currentFrame * (float)img.width / frame_amount;	
			}

			DrawTextureRec (img, FrameRec, pos, color);
		};

		void CheckAnimationState()
		{
			if (IsKeyDown (KEY_A) || IsKeyDown (KEY_D)) {
				_AnimationState = AnimationState::WALKING;
			} else if (IsKeyDown (KEY_SPACE)) {
				_AnimationState = AnimationState::JUMPING;
			} else {
				_AnimationState = AnimationState::IDLE;
			}
		};

		void FLipTextureHoriz() { img.width = -img.width; };
};

#endif