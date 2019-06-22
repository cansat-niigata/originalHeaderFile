#include "UseMotorSTM32f103.h"

/*----------------------------------
  モーターを指定時間、指定したパルス値で正転させるメソッド
  ----------------------------------
  引数  : time(int)  正転させる時間（単位はミリ秒）
         PULSE(int) 正転に使うパルス値
  戻り値 : なし
  機能  : PLUSEでモーターを正転させる
  ----------------------------------*/
void UseMotor::rotationNormal(int PULSE) {
	analogWrite(normal, PULSE);
	analogWrite(invert, 0);
}

void UseMotor::rotationNormal(){
  analogWrite(normal, 255);
  analogWrite(invert, 0);
}

/*----------------------------------
  モーターを指定時間、指定したパルス値で逆転させるメソッド
  ----------------------------------
  引数  : time(int)  逆転させる時間（単位はミリ秒）
         PULSE(int) 逆転に使うパルス値
  戻り値 : なし
  機能  : timeだけPLUSEでモーターを逆転させる
         delay()を使用しているので注意
		 時間を指定しない場合はずっとまわり続ける
  ----------------------------------*/
void UseMotor::rotationInvert(int PULSE) {
	analogWrite(normal, 0);
	analogWrite(invert, PULSE);
}

void UseMotor::rotationInvert(){
  analogWrite(normal, 0);
  analogWrite(invert, 255);
}
/*---------------------------------
  モーターでブレーキを使用するメソッド
  ---------------------------------
  引数  : なし
  戻り値 : なし
  機能  : ブレーキを使用する
         モーターを停止させるだけならばstop()の
		 使用を推奨
  ---------------------------------*/
void UseMotor::brake() {
	analogWrite(normal, 255);
	analogWrite(invert, 255);
}

/*---------------------------------
  モーターを停止させるメソッド
  ---------------------------------
  引数  : なし
  戻り値 : なし
  機能  : モーターを停止させる
  ---------------------------------*/
void UseMotor::stop() {
	analogWrite(normal, 0);
	analogWrite(invert, 0);
}