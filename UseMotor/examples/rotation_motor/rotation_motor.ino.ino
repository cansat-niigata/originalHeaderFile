/*----------------------------------------------
 * モーターを正転、逆転
 * PWM値を用いて出力を調整して正転、逆転
 *                            made by s.w
 -----------------------------------------------*/
 
 /* UseMotor.hを使ってモーターを回転させる
  * Arduino unoを使用することを想定しています
  * 
  */
#include <UseMotor.h>

UseMotor motor(5, 3);

void setup() {
}

void loop() {
  motor.rotationNormal();  //正転
  delay(1000);
  motor.stop();

  motor.rotationInvert();  //逆転
  delay(1000);
  motor.stop();

  motor.rotationNormal_p(150);  //pwm値を150にして正転
  delay(1000);
  motor.stop();

  motor.rotationInvert_p(150); //pwm値を150にして逆転
  delay(1000);
  motor.stop();
}
