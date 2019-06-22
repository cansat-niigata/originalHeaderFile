/*--------------------
  モータを操作するためのライブラリ
  --------------------*/
#ifndef __Class_UseMotorSTM32f103
#define __Class_UseMotorSTM32f103

#include "arduino.h"

class UseMotor {
	
	private:
		int normal; //前進時にHIGHとするピン
		int invert; //後退時にHIGHとするピン
	
	public:
		UseMotor(int normal=0, int invert=0) : normal(normal), invert(invert){};
		void set_normalPin(int normal){ this->normal = normal; };
		void set_invertPin(int invert){ this->invert = invert; };
		void rotationNormal(int PULSE); //PULSEで正回転
		void rotationNormal();
		void rotationInvert(int PULSE); //PULSEで逆回転
		void rotationInvert();
		void brake();
		void stop();
};

#endif
