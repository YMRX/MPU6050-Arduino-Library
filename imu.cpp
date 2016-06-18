/*
  imu.cpp --> MPU6050 Libary
  @author: c4p7a1n_r007
  @version: 1.0
*/

#include "Arduino.h"
#include "imu.h"
#include <Wire.h>

double offset[3];
int start = 0;

IMU::IMU() {
  // do something
}


void IMU::setup_register() {
  Wire.begin();

  Wire.beginTransmission(0x68);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();

  //Configure the accelerometer (+/-8g)
  Wire.beginTransmission(0x68);
  Wire.write(0x1C);
  Wire.write(0x10);
  Wire.endTransmission();

  //Configure the gyro (500dps full scale)
  Wire.beginTransmission(0x68);
  Wire.write(0x1B);
  Wire.write(0x08);
  Wire.endTransmission();
}

void IMU::calibrateGyroscope() {

  // Calibrate the gyroscope
  for (int cal_int = 0; cal_int < 2000 ; cal_int ++) {
    start ++;
    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    getRaw(&ax, &ay, &az, &gx, &gy, &gz);
    offset[0] += gx;
    offset[1] += gy;
    offset[2] += gz;

    delay(3);
    if (start == 10) {
      digitalWrite(13, !digitalRead(13));
      start = 0;
    }
  }
  offset[0] /= 2000;
  offset[1] /= 2000;
  offset[2] /= 2000;
}

void IMU::getRaw(int16_t* ax, int16_t* ay, int16_t* az, int16_t* gx, int16_t* gy, int16_t* gz) {

  Wire.beginTransmission(0x68);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(0x68, 14, true);

  while (Wire.available() < 14);

  // Acclerometer
  *ax = (int16_t) (Wire.read() << 8 | Wire.read());
  *ay = (int16_t) (Wire.read() << 8 | Wire.read());
  *az = (int16_t) (Wire.read() << 8 | Wire.read());

  // Temprature
  Wire.read() << 8 | Wire.read();

  // Gyroscope
  *gx = (int16_t) (Wire.read() << 8 | Wire.read());
  *gy = (int16_t) (Wire.read() << 8 | Wire.read());
  *gz = (int16_t) (Wire.read() << 8 | Wire.read());
}

void IMU::getGyroscope(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z) {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  getRaw(&ax, &ay, &az, &gx, &gy, &gz);

  *gyro_x = gx - offset[0];
  *gyro_y = gy - offset[1];
  *gyro_z = gz - offset[2];


}

void IMU::getAcclerometer(int16_t* acc_x, int16_t* acc_y, int16_t* acc_z) {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  getRaw(&ax, &ay, &az, &gx, &gy, &gz);

  *acc_x = ax;
  *acc_y = ay;
  *acc_z = az;


}

void IMU::get6Motion(int16_t* gyro_x, int16_t* gyro_y, int16_t* gyro_z, int16_t* acc_x, int16_t* acc_y, int16_t* acc_z) {

  int16_t ax, ay, az;
  int16_t gx, gy, gz;
  getRaw(&ax, &ay, &az, &gx, &gy, &gz);

  *gyro_x = gx - offset[0];
  *gyro_y = gy - offset[1];
  *gyro_z = gz - offset[2];

  
  *acc_x = ax;
  *acc_y = ay;
  *acc_z = az;

}





