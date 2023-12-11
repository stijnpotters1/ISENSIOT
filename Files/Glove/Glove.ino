#include <SoftwareSerial.h>

#define TX 2
#define RX 3

SoftwareSerial BTSerial(TX, RX);

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
