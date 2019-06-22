#include <Wire.h>
//#include "Arduino.h"
#include "Press.h"
#define BME280_ADDRESS 0x76
Press::Press(){};

void Press::readTrim()
{
    uint8_t data[32],k=0;
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0x88);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,24);      
    while(Wire.available()){
        data[k] = Wire.read();
        k++;
    }
    
    Wire.beginTransmission(BME280_ADDRESS);    
    Wire.write(0xA1);                          
    Wire.endTransmission();                    
    Wire.requestFrom(BME280_ADDRESS,1);        
    data[k] = Wire.read();                     
    k++;                                       
    
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0xE1);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,7);        
    while(Wire.available()){
        data[k] = Wire.read();
        k++;    
    }
    dig_T1 = (data[1] << 8) | data[0];
    dig_T2 = (data[3] << 8) | data[2];
    dig_T3 = (data[5] << 8) | data[4];
    dig_P1 = (data[7] << 8) | data[6];
    dig_P2 = (data[9] << 8) | data[8];
    dig_P3 = (data[11]<< 8) | data[10];
    dig_P4 = (data[13]<< 8) | data[12];
    dig_P5 = (data[15]<< 8) | data[14];
    dig_P6 = (data[17]<< 8) | data[16];
    dig_P7 = (data[19]<< 8) | data[18];
    dig_P8 = (data[21]<< 8) | data[20];
    dig_P9 = (data[23]<< 8) | data[22];
    dig_H1 = data[24];
    dig_H2 = (data[26]<< 8) | data[25];
    dig_H3 = data[27];
    dig_H4 = (data[28]<< 4) | (0x0F & data[29]);
    dig_H5 = (data[30] << 4) | ((data[29] >> 4) & 0x0F); 
    dig_H6 = data[31];                                  
}

void Press::writeReg(uint8_t a,uint8_t b)
{
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(a);
    Wire.write(b);
    Wire.endTransmission();    
}

void Press::readData()
{
    int j = 0;
    uint32_t data_r[8];
    Wire.beginTransmission(BME280_ADDRESS);
    Wire.write(0xF7);
    Wire.endTransmission();
    Wire.requestFrom(BME280_ADDRESS,8);
    while(Wire.available()){
        data_r[j] = Wire.read();
        j++;
    }
    pres_raw = (data_r[0] << 12) | (data_r[1] << 4) | (data_r[2] >> 4);
    temp_raw = (data_r[3]<< 12) | (data_r[4] << 4) | (data_r[5] >> 4);
    hum_raw  = (data_r[6]<< 8) | data_r[7];
}

signed long int Press::calc_t(signed long int t)
{
    var_t1 = ((((t >> 3) - ((signed long int)dig_T1<<1))) * ((signed long int)dig_T2)) >> 11;
    var_t2 = (((((t >> 4) - ((signed long int)dig_T1)) * ((t>>4) - ((signed long int)dig_T1))) >> 12) * ((signed long int)dig_T3)) >> 14;
    
    t_fine = var_t1 + var_t2;
    T = (t_fine * 5 + 128) >> 8;
    return T; 
}

unsigned long int Press::calc_p(signed long int p)
{
    var_p1 = (((signed long int)t_fine)>>1) - (signed long int)64000;
    var_p2 = (((var_p1>>2) * (var_p1>>2)) >> 11) * ((signed long int)dig_P6);
    var_p2 = var_p2 + ((var_p1*((signed long int)dig_P5))<<1);
    var_p2 = (var_p2>>2)+(((signed long int)dig_P4)<<16);
    var_p1 = (((dig_P3 * (((var_p1>>2)*(var_p1>>2)) >> 13)) >>3) + ((((signed long int)dig_P2) * var_p1)>>1))>>18;
    var_p1 = ((((32768+var_p1))*((signed long int)dig_P1))>>15);
    if (var_p1 == 0)
    {
        return 0;
    }    
    P = (((unsigned long int)(((signed long int)1048576)-p)-(var_p2>>12)))*3125;
    if(P<0x80000000)
    {
       P = (P << 1) / ((unsigned long int) var_p1);   
    }
    else
    {
        P = (P / (unsigned long int)var_p1) * 2;    
    }
    var_p1 = (((signed long int)dig_P9) * ((signed long int)(((P>>3) * (P>>3))>>13)))>>12;
    var_p2 = (((signed long int)(P>>2)) * ((signed long int)dig_P8))>>13;
    P = (unsigned long int)((signed long int)P + ((var_p1 + var_p2 + dig_P7) >> 4));
    return P;
}

unsigned long int Press::calc_h(signed long int h)
{
    v_x1 = (t_fine - ((signed long int)76800));
    v_x1 = (((((h << 14) -(((signed long int)dig_H4) << 20) - (((signed long int)dig_H5) * v_x1)) + 
              ((signed long int)16384)) >> 15) * (((((((v_x1 * ((signed long int)dig_H6)) >> 10) * 
              (((v_x1 * ((signed long int)dig_H3)) >> 11) + ((signed long int) 32768))) >> 10) + (( signed long int)2097152)) * 
              ((signed long int) dig_H2) + 8192) >> 14));
   v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((signed long int)dig_H1)) >> 4));
   v_x1 = (v_x1 < 0 ? 0 : v_x1);
   v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
   return (unsigned long int)(v_x1 >> 12);   
}

void Press::set()
{
    uint8_t osrs_t = 1;             //Temperature oversampling x 1
    uint8_t osrs_p = 3;             //Pressure oversampling x 4
    uint8_t osrs_h = 1;             //Humidity oversampling x 1
    uint8_t mode = 3;               //Normal mode
    uint8_t t_sb = 5;               //Tstandby 1000ms
    uint8_t filter = 0;             //Filter off 
    uint8_t spi3w_en = 0;           //3-wire SPI Disable
    
    uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
    uint8_t config_reg    = (t_sb << 5) | (filter << 2) | spi3w_en;
    uint8_t ctrl_hum_reg  = osrs_h;
    
    //Serial.begin(9600);
    //Wire.begin();
    
    writeReg(0xF2,ctrl_hum_reg);
    writeReg(0xF4,ctrl_meas_reg);
    writeReg(0xF5,config_reg);
    readTrim();                    
}

void Press::measPress()
{
   readData();
    
    temp_cal = calc_t(temp_raw);
    press_cal = calc_p(pres_raw); 
    hum_cal = calc_h(hum_raw);
    temp_act = (double)temp_cal / 100.0;
    press_act = (double)press_cal / 100.0;
    hum_act = (double)hum_cal / 1024.0;
    
}
