#ifndef __Class_PID
#define __Class_PID

#include "arduino.h"

class PID{
	private:
		double P;
		double I;
		double D;
		double preP;
		double target; //目標値
		double conVar; //制御量
		double kp; //P制御の係数
		double ki; //I制御の係数
		double kd; //D制御の係数
		double dt; //微積分に使う微小区間の値
	public:
		PID() : target(0), conVar(0), kp(0), dt(1), ki(0), kd(0), P(0), I(0), D(0), preP(0){};
		PID(double target, double kp,double dt=0,double ki=0, double kd=0):target(target),kp(kp),dt(dt),ki(ki),kd(kd),P(0),I(0),D(0),preP(0){};
		void set_Target(double target) { this->target = target; };
		void set_conVar(double conVar) { this->conVar = conVar; };
		void set_Kp(double kp) { this->kp = kp; };
		void set_Ki(double ki) { this->ki = ki; };
		void set_Kd(double kd) { this->kd = kd; };
		void set_dt(double dt) { this->dt = dt; };
		double get_conVar() { return conVar; };
		void update_conVar(double getValue); //読み込んだ値からconVarを更新する
		void update_conVar(int getValue); //int型用
};

#endif