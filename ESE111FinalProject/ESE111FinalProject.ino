#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SoftwareSerial.h>
/* This driver reads raw data from the BNO055

   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 5V DC
   Connect GROUND to common ground

   History
   =======
   2015/MAR/03  - First release (KTOWN)
*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (10)

Adafruit_BNO055 bno = Adafruit_BNO055();

/**************************************************************************/
/*
    Arduino setup function (automatically called at startup)
*/
/**************************************************************************/
SoftwareSerial BTSerial(2, 3); //TX RX
int red = 9;
int green = 10;
int blue = 11;

void setup(void)
{
  BTSerial.begin(9600);
  Serial.begin(9600);


  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(9,OUTPUT);

  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }

  delay(1000);
}

/**************************************************************************/
/*
    Arduino loop function, called once 'setup' is complete (your own code
    should go here)
*/
/**************************************************************************/
void loop(void)
{
  // Possible vector values can be:
  // - VECTOR_ACCELEROMETER - m/s^2
  // - VECTOR_MAGNETOMETER  - uT
  // - VECTOR_GYROSCOPE     - rad/s
  // - VECTOR_EULER         - degrees
  // - VECTOR_LINEARACCEL   - m/s^2
  // - VECTOR_GRAVITY       - m/s^2
   imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);

  /* Display the floating point data */
  // tone(9,euler.z()*100-euler.y()*10+euler.x());

   int x = map(euler.x(), -10, 10, 0, 1023);
   int y = map(euler.y(), -10, 10, 0, 1023);
   int z = map(euler.z(), -10, 10, 0, 1023);
   
  // tone(6, euler.z()*100-10*euler.y()+euler.x());
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);

  BTSerial.print(x);
  BTSerial.print(",");
  BTSerial.print(y);
  BTSerial.print(",");
  BTSerial.println(z);
  
  analogWrite(red, x);
  analogWrite(green,y);
  analogWrite(blue,z);


  
  delay(BNO055_SAMPLERATE_DELAY_MS);
  
}



// 































