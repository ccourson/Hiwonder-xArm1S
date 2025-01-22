#include <xArmServoController.h>
//#include <SoftwareSerial.h>

// To use SoftwareSerial:
// 1. Uncomment include statement above and following block.
// 2. Update xArmServoController with mySerial.
// 3. Change Serial1.begin to mySerial.begin.
/* 
#define rxPin 2
#define txPin 3

SoftwareSerial mySerial = SoftwareSerial(rxPin, txPin);
*/
xArmServoController myArm = xArmServoController(xArm, Serial1);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  int millivolts = myArm.getBatteryVoltage();
  Serial.print("Battery Voltage (ma): ");
  Serial.println(millivolts, DEC);

  // Your setup here.
}

void loop() {
  // Your code here.
}