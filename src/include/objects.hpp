#ifndef FGTH_OBJECTS_HEADER
#define FGTH_OBJECTS_HEADER

#include "raylib.h"
#include "animated_sprites.hpp"
#include <iostream>
#include <string>
#include <cmath>
#include <map>

//----------------------------------------------------------------------------------------
enum class EntityStates
{
	IDLE   , WALKING, 
	JUMPING, 
	ATTACK , COMBO
};
//----------------------------------------------------------------------------------------

class ObjectRoot
{
	public:
		Vector2  pos;
		Vector2  size;
};

class DynamicObject: public ObjectRoot
{
	public:
		Vector2 vel;
		Vector2 speed;
		float 	gravity;
};

void updateGravity (DynamicObject& a, float delT);

class Player : public DynamicObject
{
	public:
		bool  			canJump;
		float 			HP;
		float 			damage;
		bool  			damage_counted;
		bool 			isJumping = false;

		int attacks_count;
		float late_;
		bool isAttacking = false;
		bool IsTimerActive = false;
		AnimatedSprite _Animation;
		
	public:
		Player();
		EntityStates getCurrentState() const { return _currentstate; };
		void 		 setState (EntityStates newState);

		void UpdateMoving 		 (float delT);
		void UpdateJumping 		 (float delT);
		void checkState ();

		void checkCurrentAnimation ();
		void setAnimationFlip ();

		void delayPunch			 (float delT);
			
			template <class A>
		void DamageCalculating (A& a)
		{
			if (damage_counted == false && a.damage_counted == false) {
				damage *= a.damage_coefficient;
				damage = damage / a.HP;
				damage_counted = true;
				a.damage_counted = true;
			}
		};
			
			template <class A>
		void takeDamage (A& a, bool collision)
		{
			if (collision && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
				a.damage_coefficient -= damage;
			}
		};

		void checkCombo();

	private:
		EntityStates _currentstate;
};


class Boss : public DynamicObject
{
	public:
		Vector2 speed;
		float 	HP;
		float 	damage;
		bool  	damage_counted;
		float 	damage_coefficient;
};

#endif