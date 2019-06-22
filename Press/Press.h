#ifndef Press_h
#define Press_h
#include "Arduino.h"

class Press{
  public:
    Press();
    void set();
	  void measPress();
    double temp_act = 0.0, press_act = 0.0,hum_act=0.0;
   private:
    void readTrim();
    void readData();
    void writeReg(uint8_t, uint8_t);
    signed long int calc_t(signed long int t);
    unsigned long int calc_p(signed long int p);
    unsigned long int calc_h(signed long int h);
    unsigned long int hum_raw,temp_raw,pres_raw,P,press_cal,hum_cal;
    signed long int t_fine,var_t1, var_t2,T,var_p1, var_p2,v_x1,temp_cal;
    uint16_t dig_T1;
     int16_t dig_T2;
     int16_t dig_T3;
    uint16_t dig_P1; 
     int16_t dig_P2;
     int16_t dig_P3;
     int16_t dig_P4;
     int16_t dig_P5;
     int16_t dig_P6;
     int16_t dig_P7;
     int16_t dig_P8;
     int16_t dig_P9;
     int8_t  dig_H1;
     int16_t dig_H2;
     int8_t  dig_H3;
     int16_t dig_H4;
     int16_t dig_H5;
     int8_t  dig_H6; 
};
#endif
