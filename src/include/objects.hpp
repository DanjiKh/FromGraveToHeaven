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
		bool IsAttacking = false;
		bool IsTimerActive = false;
		AnimatedSprite _Animation;
		
	public:
		Player();
		EntityStates getCurrentState() const { return _currentstate; };
		void 		 setState (EntityStates newState);

		void UpdateMoving 		 (float delT);
		void UpdateJumping 		 (float delT);
		void SetAnimationState 	 ();

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

template <class A, class B, class C, class D>
void combo_check(A& a, B& b, C& c, D& d, Texture2D first_punch, Texture2D second_punch, Texture2D third_punch)
		{
			switch (a.attacks_count) {
				case 1 :
					a.IsTimerActive = true;

					if (!b.isFinished) {
						a.IsTimerActive = false;

                        c.isFinished = false;
                        c.frameCounter = 1;
                        d.isFinished = false;
                        d.frameCounter = 1;

                       	b.Draw();

					} else {
						a.IsAttacking = false;
						a.IsTimerActive = true;
					}

					if (a.late_ <= 2.0f) {
						a.attacks_count = 0; 
						a.late_ = 3.0f;
						a.IsAttacking = false;
						b.isFinished = false;
                        b.frameCounter = 1;
                        a.IsTimerActive = false;
					}

					break;

				case 2 :
					if (a.late_ >= 2.0f) { 
						if(!c.isFinished) {
							a.IsTimerActive = false;

                        	b.isFinished = false;
                        	b.frameCounter = 1;
                        	d.isFinished = false;
                        	d.frameCounter = 1;

                        	c.Draw();

						} else {
							a.IsAttacking = false;
							a.IsTimerActive = true;
						}
					} else if(a.late_ <= 2.0f) {
						a.attacks_count = 0; 
						a.late_ = 3.0f;
						a.IsAttacking = false;
						b.isFinished = false;
                        b.frameCounter = 1;
                        a.IsTimerActive = false;
					}

					break; 

				case 3 :
					if (a.late_ >= 1.0f) {
						if (!d.isFinished) {
							a.IsTimerActive = false;

                        	c.isFinished = false;
                        	c.frameCounter = 1;
                        	b.isFinished = false;
                        	b.frameCounter = 1;

                        	d.Draw();
						} else {
							a.IsAttacking = false;
							a.IsTimerActive = true;

							a.late_ = 3.0f;
							a.attacks_count = 0;
							a.IsAttacking = false;

							b.isFinished = false;
                    		b.frameCounter = 1;
						}
					} else if(a.late_ <= 1.0f){
						a.attacks_count = 0; 
						a.late_ = 3.0f;
						a.IsAttacking = false;
						b.isFinished = false;
						c.isFinished = false;
                        b.frameCounter = 1;
                        c.frameCounter = 1;
                        a.IsTimerActive = false;
					}

					break;
			}
		};

#endif