// MPU9250.h ???C?u????  loop ?????read()?????o???????????
#include <Wire.h>

#ifndef _MPU9250_h
#define _MPU9250_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

/////////////////////////MPU9250////////////////////////////
#define MPU9250_ADDRESS 0x68//I2CでのMPU9250のスレーブアドレス

#define PWR_MGMT_1 0x6b//電源管理のアドレス、スリープモード解除用
#define INT_PIN_CFG 0x37//磁気センサのバイパスモード設定用のアドレス

#define ACCEL_CONFIG 0x1c//加速度センサ設定用のアドレス
#define ACCEL_FS_SEL_2G 0x00//加速度センサのレンジ(2G)
#define ACCEL_FS_SEL_4G 0x08//加速度センサのレンジ(4G)
#define ACCEL_FS_SEL_8G 0x10//加速度センサのレンジ(8G)
#define ACCEL_FS_SEL_16G 0x18//加速度センサのレンジ(16G)

#define GYRO_CONFIG 0x1b//ジャイロセンサ設定用のアドレス
#define GYRO_FS_SEL_250DPS 0x00//ジャイロセンサのレンジ(250DPS)
#define GYRO_FS_SEL_500DPS 0x08//ジャイロセンサのレンジ(500DPS)
#define GYRO_FS_SEL_1000DPS 0x10//ジャイロセンサのレンジ(1000DPS)
#define GYRO_FS_SEL_2000DPS 0x18//ジャイロセンサのレンジ(2000DPS)

#define AK8963_ADDRESS 0x0c//磁気センサのスレーブアドレス
#define CNTL1 0x0a//磁気センサ設定用のアドレス
#define CNTL1_MODE_SEL_8HZ 0x12//磁気センサの出力周期(8Hz)
#define CNTL1_MODE_SEL_100HZ 0x16//磁気センサの出力周期(100Hz)
#define ST1 0x02//データ読み込み用フラッグのアドレス
///////////////////////////////////////////////////////////


class MPU9250
{
private:
	void i2cread(uint8_t Address, uint8_t Register, uint8_t NBytes, volatile uint8_t* Data);
	void i2cwrite(uint8_t Address, uint8_t Register, volatile uint8_t Data);

	volatile float accRange;//計算で使用するので、選択したレンジを入力する定数
	volatile float gyroRange;//計算で使用するので、選択したレンジを入力する定数

	volatile uint8_t accGyroTempData[14];//センサからのデータ格納用配列
	volatile uint8_t magneticData[7];//センサからのデータ格納用配列
	volatile uint8_t ST1Bit;//磁気センサのフラッグ

	volatile int16_t ax;//16bitの出力データ
	volatile int16_t ay;//16bitの出力データ
	volatile int16_t az;//16bitの出力データ
	volatile int16_t gx;//16bitの出力データ
	volatile int16_t gy;//16bitの出力データ
	volatile int16_t gz;//16bitの出力データ
	volatile int16_t tempMPU9250Raw;//16bitの出力データ
	volatile int16_t mx;//16bitの出力データ
	volatile int16_t my;//16bitの出力データ
	volatile int16_t mz;//16bitの出力データ
	unsigned int times; //加速度センサからのデータ取得回数
public:
	MPU9250();
	~MPU9250();
	
	void set(int accrange,int gyrorange);
	void read();
	void calc();

	volatile float accX;//加速度センサからもとめた重力加速度
	volatile float accY;//加速度センサからもとめた重力加速度
	volatile float accZ;//加速度センサからもとめた重力加速度

	volatile float gyroX;//ジャイロセンサから求めた角速度
	volatile float gyroY;//ジャイロセンサから求めた角速度
	volatile float gyroZ;//ジャイロセンサから求めた角速度
	volatile float tempMPU9250;//MPU9250の温度

	volatile float magX;//磁気センサから求めたuT
	volatile float magY;//磁気センサから求めたuT
	volatile float magZ;//磁気センサから求めたuT

};
#endif

