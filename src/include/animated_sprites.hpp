#pragma once

#include "raylib.h"

#include <string>
#include <vector>
#include <map>

struct Sprite;


class AnimatedSprite
{
	public:
		enum class PlayMode
		{
			LOOP,
			SINGLE
		};
		enum class FlipTexture
		{
			NONE,
			HORIZONTAL,
			VERTICAL
		};

	public:
		std::string getCurrAnimation() const;

		void addAnimation (std::string newName, int img_id, int frames, float fps, PlayMode mode);
		void setAnimation (std::string newState);
		void setPlayMode  (PlayMode mode);
		
		void Draw (Vector2& pos, float ftime, Color tint);

	public:
		PlayMode 	play_mode = PlayMode::LOOP;
		FlipTexture _flip	  = FlipTexture::NONE;

		int       	frame_amount;
		
		int  		texture_width;
		bool 		isFinished = false;
		Rectangle 	FrameRec;
		float 		frameSpeed;
		float 		_currFps   	 = 0;
		int 		frameCounter = 0;

	protected:
		std::string curr_state;
		std::map<std::string, Sprite> loaded_anims;

};

struct Sprite 
{
	int   img_id;
	int   frames_amount;
	float fps;
	AnimatedSprite::PlayMode mode;
};

