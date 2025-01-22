#include <SoftwareSerial.h>
#include <xArmServoController.h>

#define rxPin 2
#define txPin 3

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
xArmServoController myArm = xArmServoController(LeArm, mySerial);

void setup() {
  mySerial.begin(9600);

  // Your setup here.
}

void loop() {
  // Your code here.
}