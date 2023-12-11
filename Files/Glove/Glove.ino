#include <SoftwareSerial.h>

#define TX 2
#define RX 3

SoftwareSerial BTSerial(TX, RX);

String servoNr = "";  
String degrees = ""; 

void sendData(String servoNr, String degrees) {
  String message = "s" + servoNr + ": " + degrees;
  int message_len = message.length() + 1; 

  // Prepare the character array (the buffer) 
  char char_array[message_len];
  
  // Copy it over 
  message.toCharArray(char_array, message_len);

  BTSerial.write(char_array);
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(38400);
  BTSerial.begin(38400);
}

void loop() {
  // put your main code here, to run repeatedly:
    Serial.println("Enter the servo nr.");  
    while (Serial.available() == 0) {}  
    servoNr = Serial.readString(); //Reading the Input string from Serial port.  
    Serial.println("Enter the degrees");  
    while (Serial.available() == 0) {}  
    degrees = Serial.readString();

    servoNr.trim();
    degrees.trim();

    sendData(servoNr, degrees);
}
