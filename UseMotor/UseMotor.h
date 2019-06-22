/*--------------------
  モータを操作するためのライブラリ
  --------------------*/
#ifndef __Class_UseMotor
#define __Class_UseMotor

#include "arduino.h"

class UseMotor {
	
	private:
		int normal; //前進時にHIGHとするピン
		int invert; //後退時にHIGHとするピン
	
	public:
		UseMotor(int normal=0, int invert=0) : normal(normal), invert(invert){};
		void set_normalPin(int normal){ this->normal = normal; };
		void set_invertPin(int invert){ this->invert = invert; };
		void rotationNormal(int time); //timeミリ秒間正回転
		void rotationNormal();         //正回転
		void rotationInvert(int time); //timeミリ秒間逆回転
		void rotationInvert();         //逆回転
		void rotationNormal_p(int PULSE, int time); //timeミリ秒間PULSEで正回転
		void rotationNormal_p(int PULSE);           //PULSEで正回転
		void rotationInvert_p(int PULSE, int time); //timeミリ秒間PULSEで逆回転
		void rotationInvert_p(int PULSE); //PULSEで逆回転
		void brake();
		void stop();
};

#endif
