#include <xArmServoController.h>

xArmServoController myArm = xArmServoController(xArm, Serial1);

void setup() {
  Serial1.begin(9600);

  // Your setup here.
}

void loop() {
  // Your code here.
}