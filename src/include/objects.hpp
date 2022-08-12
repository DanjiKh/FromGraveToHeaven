#ifndef FGTH_OBJECTS_HEADER
#define FGTH_OBJECTS_HEADER

#include "iostream"

#include "raylib.h"
#include "vf2d.hpp"
#include <string>

//----------------------------------------------------------------------------------------
enum class AnimationState
{
	IDLE 		, WALKING, 
	JUMPING		, ATTACK,
	COMBO
}; AnimationState _AnimationState;

class ObjectRoot
{
	public:
		Vector2  pos;
		vf2d  size;
};

/*
	+----------------------------------------------+
	|          Branch for dynamic objects          |			
	+----------------------------------------------+
*/
class DynamicObject: public ObjectRoot
{
	public:
		vf2d vel;
		float gravity;
};

class Player : public DynamicObject
{
	public:
		vf2d speed;
		bool jump;
		float HP;
		float damage;
		bool damage_counted;
};

class Boss : public DynamicObject
{
	public:
		vf2d speed;
		float HP;
		float damage;
		bool damage_counted;
};

class AnimatedObject : public ObjectRoot
{
	public:
		std::string title;
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
		void DrawAnimatedObject(){
			frameCounter++;

			if(frameCounter >= (60/frameSpeed))
			{
				frameCounter = 0;
				currentFrame++;

				if (currentFrame > frame_amount)
					currentFrame = 0;
				FrameRec.x = (float)currentFrame*(float)img.width/frame_amount;
			}
			DrawTextureRec(img, FrameRec, pos, color);
		}

		void CheckAnimationState()
		{
			if (IsKeyDown(KEY_A) || IsKeyDown(KEY_D))
				_AnimationState = AnimationState::WALKING;
			else if (IsKeyDown(KEY_SPACE))
				_AnimationState = AnimationState::JUMPING;
			else
				_AnimationState = AnimationState::IDLE;
		};

};

#endif