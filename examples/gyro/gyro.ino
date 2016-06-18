/*
  gyro.ino --> MPU6050 Libary
  @author: YMRX
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
  
  /*
    A Complementary fliter is used to reduce the noise of the sensor to get better results.
    Also we need to divide the direct Output (gyro_x) by 65.5 to convert the sensor data into 
    deegres per second. You can look up more detailted information on the Datasheet of the sensor-
    https://www.invensense.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf 
  */
  
  gyro_x_output = (gyro_x_output * 0.8) + ((gyro_x / 65.5) * 0.2);                    
  gyro_y_output = (gyro_y_output * 0.8) + ((gyro_y / 65.5) * 0.2);
  gyro_z_output = (gyro_z_output * 0.8) + ((gyro_z / 65.5) * 0.2);

    
  // Print the scaled sensor data
  Serial.print(gyro_x_output); Serial.print("\t");
  Serial.print(gyro_y_output); Serial.print("\t"); 
  Serial.print(gyro_z_output); Serial.print("\n");                                             

  while (micros() - loop_timer < 4000);                                           // simulate a 250Hz cycle                             
  loop_timer = micros();                                               


}
