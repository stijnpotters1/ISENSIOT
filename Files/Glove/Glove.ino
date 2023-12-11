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
    BTSerial.write("s3 150");
    delay(2000);
}
