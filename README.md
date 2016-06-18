# MPU6050-Arduino-Library
This is a simple library programmed my self. I hope I can help people searching for a simple and understandable library for their sensor.
I am not responsable for any damage! You can use this library in your projects when you link this to this site. I would be glad if you can help with the development of this library :D

Happy coding !!
YMRX

#WIRING:
VCC  -  5V\n
GND  -  GND
SDA  -  A4
SCL  -  A5
LED - 13

#USAGE:

firstly you have to include the include the Wire.h Library:
    #include "Wire.h"

the you need to create an objekt:
    IMU sensor;

to setup the Sensor use this funktions:
    sensor.setup_register();
    delay(3000);                    // give the sensor time to start
    sensor.calibrateGyroscope();

you can get Sensor readings by using this:
    int16_t gyro_x, gyro_y, gyro_z;
    senor.getGyroscope(&gyro_x, &gyro_y, &gyro_z);
