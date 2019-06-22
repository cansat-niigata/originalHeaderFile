#include "UseMotor.h"

/*----------------------------------
  モーターを指定時間正転させるメソッド
  ----------------------------------
  引数  : time(int) 正転させる時間（単位はミリ秒）
  戻り値 : なし
  機能  : timeだけモーターを正転させる
         delay()を使用しているので注意
		 時間を指定しない場合はずっとまわり続ける
  ----------------------------------*/
  
void UseMotor::rotationNormal(int time) {
	digitalWrite(normal, HIGH);
	digitalWrite(invert, LOW);
	
	delay(time);
	
	digitalWrite(normal, LOW);
}
  
void UseMotor::rotationNormal() {
	
	digitalWrite(normal, HIGH);
	digitalWrite(invert, LOW);
}

/*----------------------------------
  モーターを指定時間逆転させるメソッド
  ----------------------------------
  引数  : time(int) 逆転させる時間（単位はミリ秒）
  戻り値 : なし
  機能  : timeだけモーターを逆転させる
         delay()を使用しているので注意
		 時間を指定しない場合はずっとまわり続ける
  ----------------------------------*/
void UseMotor::rotationInvert(int time) {
	digitalWrite(normal, LOW);
	digitalWrite(invert, HIGH);
	
	delay(time);
	
	digitalWrite(invert, LOW);
}

void UseMotor::rotationInvert() {
	digitalWrite(normal, LOW);
	digitalWrite(invert, HIGH);
}

/*----------------------------------
  モーターを指定時間、指定したパルス値で正転させるメソッド
  ----------------------------------
  引数  : time(int)  正転させる時間（単位はミリ秒）
         PULSE(int) 正転に使うパルス値
  戻り値 : なし
  機能  : timeだけPLUSEでモーターを正転させる
         delay()を使用しているので注意
		 時間を指定しない場合はずっとまわり続ける
  ----------------------------------*/
void UseMotor::rotationNormal_p(int PULSE, int time) {
	analogWrite(normal, PULSE);
	digitalWrite(invert, LOW);
	
	delay(time);
	
	digitalWrite(normal, LOW);
}

void UseMotor::rotationNormal_p(int PULSE) {
	analogWrite(normal, PULSE);
	digitalWrite(invert, LOW);
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
void UseMotor::rotationInvert_p(int PULSE, int time) {
	digitalWrite(normal, LOW);
	analogWrite(invert, PULSE);
	
	delay(time);
	
	digitalWrite(invert, LOW);
}

void UseMotor::rotationInvert_p(int PULSE) {
	digitalWrite(normal, LOW);
	analogWrite(invert, PULSE);
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
	digitalWrite(normal, HIGH);
	digitalWrite(invert, HIGH);
}

/*---------------------------------
  モーターを停止させるメソッド
  ---------------------------------
  引数  : なし
  戻り値 : なし
  機能  : モーターを停止させる
  ---------------------------------*/
void UseMotor::stop() {
	digitalWrite(normal, LOW);
	digitalWrite(invert, LOW);
}