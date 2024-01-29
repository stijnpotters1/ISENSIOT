#include <Adafruit_PWMServoDriver.h>
#include <Wire.h>
#include <SoftwareSerial.h>

#define TX 2
#define RX 3
#define N_SERVO_MOTORS 6

Adafruit_PWMServoDriver servoDriver = Adafruit_PWMServoDriver();
SoftwareSerial BTSerial(TX, RX);

const int STEP_PRECISION_SERVO = 1;
const int MAX_STEPS_PER_MOVEMENT_TICK = 10;
const int SERVO_DELAY_PER_STEP = 1;
const int PWM_FREQUENCY = 60;

String incomingCommand = "";

struct servoMotor {
  const int SERVO_PIN_NR;
  const int MAX_PWM_VALUE;
  const int MIN_PWM_VALUE;
  int currentPWMValue;
  int nextPWMValue;
};

// Order of the servos is base, waist, arm1, arm2, arm3, gripper
struct servoMotor servos[N_SERVO_MOTORS] = {{0, 600, 120, 340, 340}, {2, 600, 120, 400, 400}, {4, 600, 120, 450, 450}, {6, 600, 120, 340, 340}, {8, 600, 120, 120, 120}, {10, 600, 120, 240, 240}};

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
  if(newServoPosition < currentServoPosition) {
    for (int i = 0; i < MAX_STEPS_PER_MOVEMENT_TICK; i++) {
      int pos = currentServoPosition - STEP_PRECISION_SERVO;

      if(pos < newServoPosition) {
        pos = newServoPosition;
      }

      servoDriver.setPWM(servoPinNr, 0, pos);
      delay(SERVO_DELAY_PER_STEP);
      currentServoPosition = pos;
    }  
  } else if (newServoPosition > currentServoPosition) {
    for (int i = 0; i < MAX_STEPS_PER_MOVEMENT_TICK; i++) {
      int pos = currentServoPosition + STEP_PRECISION_SERVO;

      if(pos > newServoPosition) {
        pos = newServoPosition;
      }

      servoDriver.setPWM(servoPinNr, 0, pos);
      delay(SERVO_DELAY_PER_STEP);
      currentServoPosition = pos;
    }  
  }
}

void MoveServos() {
  for (int i = 0; i < N_SERVO_MOTORS; i++) {
    if(servos[i].currentPWMValue != servos[i].nextPWMValue) {
      MoveServoToPosition(servos[i].nextPWMValue, servos[i].currentPWMValue, servos[i].SERVO_PIN_NR);
    }
  }
}

void SetNextPWMValue(int index, int value) {
  if(servos[index].MIN_PWM_VALUE > value) {
    servos[index].nextPWMValue = servos[index].MIN_PWM_VALUE;
  } else if(servos[index].MAX_PWM_VALUE < value) {
    servos[index].nextPWMValue = servos[index].MAX_PWM_VALUE;
  } else {
    servos[index].nextPWMValue = value;
  }
}

void setup() {
  InitializeServoDriver();
  InitializeBluetoothModule();
}

void loop() {   
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingCommand = Serial.readString();
    int servoCounter = 0;
    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingCommand);

    incomingCommand = incomingCommand.substring(0, incomingCommand.length() - 2);

    int command = incomingCommand.indexOf(';');
    
    while (command != -1) {
        incomingCommand = incomingCommand.substring(command + 1);
        command = incomingCommand.indexOf(';');
    }

    Serial.println("done");
    Serial.println(incomingCommand);

    while (incomingCommand.length() > 0) {
      int index = incomingCommand.indexOf(',');
      if (index == -1) {
        if(servoCounter == (N_SERVO_MOTORS - 1)) {
          int value = incomingCommand.substring(0, incomingCommand.length()).toInt();
          SetNextPWMValue(servoCounter, value);
          Serial.println(incomingCommand.substring(0, incomingCommand.length()));
        } else {
          Serial.println("Incomming command format error!");
        }
        break;
      } else {
        Serial.println(incomingCommand.substring(0, index));
        int value = incomingCommand.substring(0, index).toInt();
        SetNextPWMValue(servoCounter, value);
        incomingCommand = incomingCommand.substring(index + 1);
        servoCounter++;
      }
    }
  }

  MoveServos();
}
