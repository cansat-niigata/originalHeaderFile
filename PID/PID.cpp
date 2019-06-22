#include "PID.h"

void PID::update_conVar(double getValue){
	P = target - getValue;
	
	I += P * dt;           //I制御に使う値
	D = (P - preP) / dt;   //D制御に使う値
	
	preP = P;                  //prePを更新

	conVar += kp * P + ki * I + kd * D; //pwmの値を更新
	if (conVar < 0) {
		conVar = 0;
	} else if (conVar > 250) {
		conVar = 250;
	}
}

void PID::update_conVar(int getValue){
	P = target - getValue;
	
	I += P * dt;           //I制御に使う値
	D = (P - preP) / dt;   //D制御に使う値
	
	preP = P;                  //prePを更新

	conVar += kp * P + ki * I + kd * D; //pwmの値を更新
	if (conVar < 0) {
		conVar = 0;
	} else if (conVar > 250) {
		conVar = 250;
	}
}