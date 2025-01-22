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
  Serial1.begin(9600);

  // xArm servo positions
   xArmServo home[] = {{1, 500},
                      {2, 500},
                      {3, 500},
                      {4, 500},
                      {5, 500},
                      {6, 500}};
  xArmServo bow[] = {{1, 650},
                     {3, 130},
                     {4, 845},
                     {5, 650}};
 
  // LeArm servo positions. To use:
  // 1. Comment out above xArmServo definitions above.
  // 2. Change xArmServoController mode to LeArm.
  // 3. Uncomment following block.
  /*
  xArmServo home[] = {{1, 1500},
                      {2, 1500},
                      {3, 1500},
                      {4, 1500},
                      {5, 1500},
                      {6, 1500}};
  xArmServo bow[] = {{1, 2365},
                     {3, 520},
                     {4, 650},
                     {5, 1035}};
    */

  myArm.setPosition(home, 6, 1000, true);
  delay(1000);
  myArm.setPosition(bow, 4, 3000, true);
  delay(1000);
  myArm.setPosition(home, 6);

  // Your setup here.
}

void loop() {
  // Your code here.
}