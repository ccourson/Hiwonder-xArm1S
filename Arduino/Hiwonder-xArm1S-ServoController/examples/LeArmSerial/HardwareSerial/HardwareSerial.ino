#include <xArmServoController.h>

xArmServoController myArm = xArmServoController(LeArm, Serial1);

void setup() {
  Serial1.begin(9600);

  // Your setup here.
}

void loop() {
  // Your code here.
}