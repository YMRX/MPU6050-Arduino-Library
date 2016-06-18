/*
  gyro.ino --> MPU6050 Libary
  @author: c4p7a1n_r007
  @version: 1.0
*/

#include <imu.h>
#include <Wire.h>

///////////////////////////////////////////////////////////////////////////////////////
//                                  VARIABLES                                        //
///////////////////////////////////////////////////////////////////////////////////////

IMU imu;
int16_t gyro_x, gyro_y, gyro_z;
float gyro_x_output, gyro_y_output, gyro_z_output;

long loop_timer;

///////////////////////////////////////////////////////////////////////////////////////
//                                      SETUP                                        //
///////////////////////////////////////////////////////////////////////////////////////

void setup() {

  Serial.begin(9600);                                       // Activate Serial connection for debugging
  
  imu.setup_register();                                     // start sensor and setup register
  delay(3000);                                              // give sensor time to start
  imu.calibrateGyroscope();                                 // calibrate for more reliable outputs
}

///////////////////////////////////////////////////////////////////////////////////////
//                                      LOOP                                         //
///////////////////////////////////////////////////////////////////////////////////////

void loop() {

  imu.getGyroscope(&gyro_x, &gyro_y, &gyro_z);                                    // get sensor readings
  
  // scale the sensor data to degrees per second
  gyro_x_output = (gyro_x_output * 0.8) + ((gyro_x / 65.5) * 0.2);                
  gyro_y_output = (gyro_y_output * 0.8) + ((gyro_y / 65.5) * 0.2);
  gyro_z_output = (gyro_z_output * 0.8) + ((gyro_z / 65.5) * 0.2);

    

  Serial.print(gyro_x_output); Serial.print("\t");
  Serial.print(gyro_y_output); Serial.print("\t"); 
  Serial.print(gyro_z_output); Serial.print("\n");                                             

  while (micros() - loop_timer < 4000);                                         // simulate a 250Hz cycle                             
  loop_timer = micros();                                               


}
