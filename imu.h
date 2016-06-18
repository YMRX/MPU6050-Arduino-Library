/*
  imu.h --> MPU6050 Libary
  @author: YMRX
  @version: 1.0
*/

#ifndef imu_h
#define imu_h

#include "Arduino.h"


class IMU
{
  public:
  
    IMU();
    void setup_register();
    void calibrateGyroscope();
	void calibrateAcclerometer();
    void getRaw(long* ax, long* ay, long* az, int64_t* gx, int64_t* gy, int64_t* gz);
    void getGyroscope(int64_t* gyro_x, int64_t* gyro_y, int64_t* gyro_z);
    void getAcclerometer(long* acc_x, long* acc_y, long* acc_z);
    
  private:
    
};

#endif

