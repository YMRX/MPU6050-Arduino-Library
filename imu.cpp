/*
  imu.cpp --> MPU6050 Libary
  @author: YMRX
  @version: 1.0
*/

#include "Arduino.h"
#include "imu.h"
#include "Wire.h"

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
    long ax, ay, az;
    int64_t gx, gy, gz;
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
void IMU::calibrateAcclerometer() {

  // Calibrate the gyroscope
  for (int cal_int = 0; cal_int < 2000 ; cal_int ++) {
    start ++;
    long ax, ay, az;
    int64_t gx, gy, gz;
    getRaw(&ax, &ay, &az, &gx, &gy, &gz);
    offset[3] += ax;
    offset[4] += ay;
    offset[5] += az;

    delay(3);
    if (start == 10) {
      digitalWrite(13, !digitalRead(13));
      start = 0;
    }
  }
  offset[3] /= 2000;
  offset[4] /= 2000;
  offset[5] /= 2000;
}

void IMU::getRaw(long* ax, long* ay, long* az, int64_t* gx, int64_t* gy, int64_t* gz) {

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

void IMU::getGyroscope(int64_t* gyro_x, int64_t* gyro_y, int64_t* gyro_z) {

  long ax, ay, az;
  int64_t gx, gy, gz;
  getRaw(&ax, &ay, &az, &gx, &gy, &gz);

  *gyro_x = gx - offset[0];
  *gyro_y = gy - offset[1];
  *gyro_z = gz - offset[2];


}

void IMU::getAcclerometer(long* acc_x, long* acc_y, long* acc_z) {

  long ax, ay, az;
  int64_t gx, gy, gz;
  getRaw(&ax, &ay, &az, &gx, &gy, &gz);

  *acc_x = ax - offset[3];
  *acc_y = ay - offset[4];
  *acc_z = az - offset[5];


}

