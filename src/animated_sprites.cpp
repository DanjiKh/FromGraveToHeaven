#include "raylib.h"
#include "include/animated_sprites.hpp"
#include "include/resources_ids.hpp"

std::string AnimatedSprite::getCurrAnimation () const
{
	return curr_state;
};

void AnimatedSprite::addAnimation (std::string newName, int img_id, int frames, float fps, PlayMode mode)
{	
	loaded_anims[newName] = Sprite { img_id, frames, fps, mode};
};

void AnimatedSprite::setAnimation (std::string newState)
{
	if (newState != curr_state) {
		curr_state = newState;
		frameCounter = 0;
		isFinished = false;
	}
};

void AnimatedSprite::Draw (Vector2& pos, float ftime, Color tint)
{
	if (loaded_anims[curr_state].mode == PlayMode::LOOP) {
		if (frameCounter >= loaded_anims[curr_state].frames_amount) {
			frameCounter = 0;
		};
		if (_currFps >= loaded_anims[curr_state].fps) {
			_currFps = 0;
			frameCounter++;
		};
	} else {
		if (!isFinished) {
			if (frameCounter >= loaded_anims[curr_state].frames_amount) {
				frameCounter = 0;
				isFinished = true;
			};
			if (_currFps >= loaded_anims[curr_state].fps) {
				_currFps = 0;
				frameCounter++;
			};
		}
	}

	Texture img = GetTexture(loaded_anims[curr_state].img_id);

	if (_flip == FlipTexture::HORIZONTAL) {
		img.width = -img.width;
	} else {
		img.width = round(img.width);
	}

	// FrameRec.heights = GetTexture(loaded_anims[curr_state].img_id).height;
	FrameRec.y = 0.0f;
	FrameRec.x = (float)frameCounter * (float)img.width / loaded_anims[curr_state].frames_amount;
	FrameRec.width  = (float) GetTexture(loaded_anims[curr_state].img_id).width / loaded_anims[curr_state].frames_amount;
	FrameRec.height = (float) GetTexture(loaded_anims[curr_state].img_id).height;

	DrawTextureRec (img, FrameRec, pos, tint);

	_currFps += ftime;
};

void AnimatedSprite::setPlayMode (PlayMode mode)
{
	play_mode = mode;
};