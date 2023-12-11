#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define TX 2
#define RX 3

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();
SoftwareSerial BTSerial(TX, RX);

const int SERVO1_PIN_NR = 0;
const int SERVO2_PIN_NR = 2;
const int SERVO3_PIN_NR = 4;
const int SERVO4_PIN_NR = 6;
const int SERVO5_PIN_NR = 8;
const int SERVO6_PIN_NR = 10;

const int SERVO_DELAY = 5;
const int PWM_FREQUENCY = 60;

int currentPositionServo1 = 0; //Servo base
int currentPositionServo2 = 0; //Servo waist
int currentPositionServo3 = 0; //Servo arm1
int currentPositionServo4 = 0; //Servo arm2
int currentPositionServo5 = 0; //Servo arm3
int currentPositionServo6 = 0; //Servo gripper

String incomingCommand = "";

void InitializeServoDriver() {
  Serial.begin(38400);
  servoDriver.begin();
  servoDriver.setPWMFreq(PWM_FREQUENCY);
  delay(10);
}

void InitializeBluetoothModule() {
  BTSerial.begin(38400);
}

void MoveServoToPosition(int newServoPosition, int &currentServoPosition, int servoPinNr) {
  Serial.println(String("Moving servo:pin(") + servoPinNr + ") from " + currentServoPosition + " to " + newServoPosition);
  if(newServoPosition <= currentServoPosition) {
    for (int pos = currentServoPosition; pos >= newServoPosition; pos -= 1) {
      servoDriver.setPWM(servoPinNr, 0, pos);
      delay(SERVO_DELAY);
    }
  } else {
    for (int pos = currentServoPosition; pos <= newServoPosition; pos += 1) {
      servoDriver.setPWM(servoPinNr, 0, pos);
      delay(SERVO_DELAY);
    }
  }
  currentServoPosition = newServoPosition;
  Serial.println(String("Movement of servo:pin(") + servoPinNr + ") is done.");
}

void setup() {
  InitializeServoDriver();
  InitializeBluetoothModule();
}

void loop() {
  // send data only when you receive data:
    
  if (BTSerial.available() > 0) {
    // read the incoming byte:

    incomingCommand = BTSerial.readString();
    
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingCommand);

    int servoNr = incomingCommand.substring(1,2).toInt();
    int servoCommand = incomingCommand.substring(4).toInt();

    switch(servoNr) {
      case 1:
        Serial.println("Servo 1");
        MoveServoToPosition(servoCommand, currentPositionServo1, SERVO1_PIN_NR);
        break;
      case 2:
        Serial.println("Servo 2");
        MoveServoToPosition(servoCommand, currentPositionServo2, SERVO2_PIN_NR);
        break;
      case 3:
        Serial.println("Servo 3");
        MoveServoToPosition(servoCommand, currentPositionServo3, SERVO3_PIN_NR);
        break;
      case 4:
        Serial.println("Servo 4");
        MoveServoToPosition(servoCommand, currentPositionServo4, SERVO4_PIN_NR);
        break;
      case 5:
        Serial.println("Servo 5");
        MoveServoToPosition(servoCommand, currentPositionServo5, SERVO5_PIN_NR);
        break;
      case 6:
        Serial.println("Servo 6");
        MoveServoToPosition(servoCommand, currentPositionServo6, SERVO6_PIN_NR);
        break;
    }
  }
}
