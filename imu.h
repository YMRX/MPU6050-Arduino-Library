/*
  imu.h --> MPU6050 Libary
  @author: c4p7a1n_r007
  @version: 1.0
*/

#ifndef imu_h
#define imu_h

#include "Arduino.h"
#include "Wire.h"

class IMU
{
  public:
  
    IMU();
    void setup_register();
    void calibrateGyroscope();
    void getRaw(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz);
    void getGyroscope(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z);
    void getAcclerometer(int16_t* acc_x, int16_t* acc_y, int16_t* acc_z);
    void get6Motion(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z, int16_t* acc_x, int16_t* acc_y, int16_t* acc_z);
    
  private:
    
};

#endif

