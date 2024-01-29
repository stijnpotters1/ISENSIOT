#include <SoftwareSerial.h>
#include <MPU6050.h>
#include "I2Cdev.h"
#include <Wire.h>

#define TX 2
#define RX 3

SoftwareSerial BTSerial(TX, RX);
MPU6050 mpu;

String servoNr = "6";  
String degrees = ""; 

const int POTENTIOMETER_PIN_NUMBER = A6;
struct MinMax {
  int min;
  int max;
};

struct MinMax servo = {120, 240};
struct MinMax pot = {600, 850}; //Eerst kijken wat echte waardes zijn
int oldValue = 0;
int oldReturnValue = 0;

void sendData(String servoNr, String degrees) {
  String message = "s" + servoNr + ": " + degrees;
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
