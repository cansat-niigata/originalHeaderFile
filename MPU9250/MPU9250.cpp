
#include "MPU9250.h"


MPU9250::MPU9250(): ax(0),ay(0),az(0),gx(0),gy(0),gz(0),mx(0),my(0),mz(0),tempMPU9250Raw(0),times(0)
{
	
}

MPU9250::~MPU9250()
{
}




void MPU9250::i2cread(uint8_t Address, uint8_t Register, uint8_t NBytes, volatile uint8_t* Data)//指定したアドレスのデータを読む関数
{
	Wire.beginTransmission(Address);//指定したアドレスと通信を始める
	Wire.write(Register);//レジスタを書き込む
	Wire.endTransmission();//通信を終了する

	Wire.requestFrom(Address, NBytes);//スレーブからNByteのデータを要求する
	uint8_t index = 0;
	while (Wire.available()) {
		Data[index++] = Wire.read();//データを読み込む
	}
}

void MPU9250::i2cwrite(uint8_t Address, uint8_t Register, volatile uint8_t Data)//指定したアドレスにデータを書き込む関数
{
	Wire.beginTransmission(Address);//指定したアドレスと通信を始める
	Wire.write(Register);//指定するレジスタを書き込む
	Wire.write(Data);//データを書き込む
	Wire.endTransmission();//通信を終了する
}

void MPU9250::set(int accrange,int gyrorange)
{
	accRange = (float)accrange;//計算で使用するので，選択したレンジを入力する
	gyroRange = (float)gyrorange;//計算で使用するので，選択したレンジを入力する
	i2cwrite(MPU9250_ADDRESS, PWR_MGMT_1, 0x00);//スリープモードを解除
	switch (accrange)
	{
	case 2:
		i2cwrite(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_2G);//加速度センサの測定レンジの設定
		break;
	case 4:
		i2cwrite(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_4G);//加速度センサの測定レンジの設定
		break;
	case 8:
		i2cwrite(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_8G);//加速度センサの測定レンジの設定
		break;
	case 16:
		i2cwrite(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_16G);//加速度センサの測定レンジの設定
		break;
	default:
		accRange = 4.0;
		i2cwrite(MPU9250_ADDRESS, ACCEL_CONFIG, ACCEL_FS_SEL_4G);//加速度センサの測定レンジの設定
		break;
	}
	switch (gyrorange)
	{
	case 250:
		i2cwrite(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_250DPS);//ジャイロセンサの測定レンジの設定
		break;
	case 500:
		i2cwrite(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_500DPS);//ジャイロセンサの測定レンジの設定
		break;
	case 1000:
		i2cwrite(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_1000DPS);//ジャイロセンサの測定レンジの設定
		break;
	case 2000:
		i2cwrite(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_2000DPS);//ジャイロセンサの測定レンジの設定
		break;
	default:
		gyroRange = 500.0;
		i2cwrite(MPU9250_ADDRESS, GYRO_CONFIG, GYRO_FS_SEL_500DPS);//ジャイロセンサの測定レンジの設定
		break;
	}
	i2cwrite(MPU9250_ADDRESS, INT_PIN_CFG, 0x02);//bypass mode(磁気センサが使用出来るようになる)
	i2cwrite(AK8963_ADDRESS, CNTL1, CNTL1_MODE_SEL_100HZ);//
}

void MPU9250::read()//MPU9250からデータを取得する関数 loop内で実行し続けcalc()が呼ばれるまで得たデータを加算し続ける
{
	//ACC&GRYO///////////////////////////////////////////////////////////////////////////
	i2cread(MPU9250_ADDRESS, 0x3b, 14, accGyroTempData); //0x3bから，14バイト分をaccGyroDataにいれる

																		  //COMPASS////////////////////////////////////////////////////////////////////////////
	i2cread(AK8963_ADDRESS, ST1, 1, &ST1Bit);//読み出し準備ができたか確認
	if ((ST1Bit & 0x01)) {
		i2cread(AK8963_ADDRESS, 0x03, 7, magneticData);//7番目の0x09(ST2)まで読まないとデータが更新されない
	}
	/*----------remove noise----------*//*
		if (ax < 1250 && ax > 850)
			ax = 0;
		if (ay < 250 && ay > -50
			ay = 0;
		if (x_ang > -1000 && x_ang < 1000)
			x_ang = 0;
		if (y_ang > -1000 && y_ang < 1000)
			y_ang = 0;
		if (z_ang > -1000 && z_ang < 1000)       //調整値は仮
			z_ang = 0;*/

	//Acc
	ax += (accGyroTempData[0] << 8) | accGyroTempData[1];//accGyroTempData[0]を左に8シフトし(<<)，accGyroTempData[1]を足し合わせる(|)
	ay += (accGyroTempData[2] << 8) | accGyroTempData[3];//accGyroTempData[2]を左に8シフトし(<<)，accGyroTempData[3]を足し合わせる(|)
	az += (accGyroTempData[4] << 8) | accGyroTempData[5];//accGyroTempData[4]を左に8シフトし(<<)，accGyroTempData[5]を足し合わせる(|)
	 //Gyro
	gx += (accGyroTempData[8] << 8) | accGyroTempData[9];//accGyroTempData[8]を左に8シフトし(<<)，accGyroTempData[9]を足し合わせる(|)
	gy += (accGyroTempData[10] << 8) | accGyroTempData[11];//accGyroTempData[10]を左に8シフトし(<<)，accGyroTempData[11]を足し合わせる(|)
	gz += (accGyroTempData[12] << 8) | accGyroTempData[13];//accGyroTempData[12]を左に8シフトし(<<)，accGyroTempData[13]を足し合わせる(|)
	

}

void MPU9250::calc()//  取得したデータの回数に応じた平均を取り単位を変換する
{
	if (times > 0)
	{
		ax /= times;
		ay /= times;
		az /= times;
		gx /= times;
		gy /= times;
		gz /= times;
	}
	accX = (float)ax * accRange / 32768.0*9.80665;//[G]に変換
	accY = (float)ay * accRange / 32768.0*9.80665;//[G]に変換
	accZ = (float)az * accRange / 32768.0*9.80665;//[G]に変換

	gyroX = (float)gz * gyroRange / 32768.0;//[deg/s]に変換
	gyroY = (float)gy * gyroRange / 32768.0;//[deg/s]に変換
	gyroZ = (float)gz * gyroRange / 32768.0;//[deg/s]に変換
	times = 0;
	ax = 0;
	ay = 0;
	az = 0;
	gx = 0;
	gy = 0;
	gz = 0;
}
