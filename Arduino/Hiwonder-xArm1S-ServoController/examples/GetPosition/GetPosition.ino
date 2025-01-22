// The getPosition function will work for xArm but not LeArm.
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

  xArmServo servos[] = {{1, 500},
                        {2, 500},
                        {3, 500},
                        {4, 500},
                        {5, 500},
                        {6, 500}};

  myArm.servoOff(); // turns off all servo motors.
  myArm.getPosition(servos, 6);
  
  for (int i = 0; i < 6; i++) {
      Serial.print("\nServo ");
      Serial.print(i, DEC);
      Serial.print(" position: ");
      Serial.print(servos[i].position);
  }  

  // Your setup here.
}

void loop() {
  // Your code here.
}