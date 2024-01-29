#include <SoftwareSerial.h>
#include <MPU6050.h>
#include "I2Cdev.h"
#include <Wire.h>

#define TX 2
#define RX 3

SoftwareSerial BTSerial(TX, RX);
MPU6050 mpu;

const float OFFSET_GY_X = 108;
const float OFFSET_GY_Y = -47;
const float OFFSET_GY_Z = 35;
const float OFFSET_ACCEL_X = -302;
const float OFFSET_ACCEL_Y = -864;
const float OFFSET_ACCEL_Z = 939;

int16_t ax, ay, az, gx, gy, gz;
String servoDegreesOne, servoDegreesTwo, servoDegreesThree, servoDegreesFour, servoDegreesFive, servoDegreesSix; 

float totalRotationX = 0.0;
float totalRotationY = 0.0;
float totalRotationZ = 0.0;

unsigned long previousMillisGyro = 0;

const float GRAVITY = 9.81;  // Acceleration due to gravity in m/s^2
unsigned long previousMillisAcceleration = 0;

float totalDistanceX = 0.0;
float totalDistanceY = 0.0;
float totalDistanceZ = 0.0;
  
const int POTENTIOMETER_PIN_NUMBER_LEFT_RIGHT = A1;
const int POTENTIOMETER_PIN_NUMBER_FORWARD_BACKWARD = A2;
const int POTENTIOMETER_PIN_NUMBER_GRIPPER = A7;

struct MinMax {
  int min;
  int max;
};

struct MinMax servoPWMReachZeroToSixHunderd = {0, 600};
struct MinMax servoPWMReachSixHunderdToZero = {600, 0};

struct MinMax joyStickReach = {0, 1000};

struct MinMax wristReachReciprocating = {-150, 150};
struct MinMax wristReachRotation = {-600, 600};
struct MinMax upDownReach = {-3500, 3500};
struct MinMax servoGripper = {120, 240};


struct MinMax pot = {450, 800}; //Eerst kijken wat echte waardes zijn
int servoDelta = 0;
int potentiometerDelta = 0;
int previousPotentiometerMeasurement = 0;


void initializeGyro() {
  mpu.initialize();
  mpu.setDLPFMode(MPU6050_DLPF_BW_5);
  
  mpu.setXGyroOffset(OFFSET_GY_X);
  mpu.setYGyroOffset(OFFSET_GY_Y);
  mpu.setZGyroOffset(OFFSET_GY_Z);
  mpu.setXAccelOffset(OFFSET_ACCEL_X);
  mpu.setYAccelOffset(OFFSET_ACCEL_Y);
  mpu.setZAccelOffset(OFFSET_ACCEL_Z);
  delay(100);
}  

String gyroMovement(int axis, struct MinMax wristReach, struct MinMax servoPWMReach, float& totalRotation) {
   unsigned long currentMillis = millis();  
   float elapsedTime = (currentMillis - previousMillisGyro) / 1000.0;

   float rotationChange = axis * elapsedTime;
   totalRotation += (int)rotationChange;

   int mappedRotation = map(totalRotation, wristReach.min, wristReach.max, servoPWMReach.min, servoPWMReach.max);

   if (mappedRotation >= 600) {
     mappedRotation = 600;
   }
   else if (mappedRotation <= 0) {
     mappedRotation = 0;
   }

   previousMillisGyro = currentMillis;

   return (String) mappedRotation;
}
  int message_len = message.length() + 1; 

  char char_array[message_len];
  
  message.toCharArray(char_array, message_len);

  BTSerial.write(char_array);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  BTSerial.begin(38400);
}

void loop() {
  gripper();
}

void gripper() {
    int currentValue = analogRead(POTENTIOMETER_PIN_NUMBER);

  if(oldValue != currentValue) {
    int servoDelta = servo.max - servo.min;
    int potDelta = pot.max - pot.min;
    int returnValue = ((float)servoDelta * ((float)currentValue /(float)potDelta)) - servo.min;
    String degrees = (String)returnValue;

    if(oldReturnValue != returnValue) {
      sendData(servoNr, degrees);
      oldReturnValue = returnValue;
      delay(2500);
    }
  }
  oldValue = currentValue;
}
