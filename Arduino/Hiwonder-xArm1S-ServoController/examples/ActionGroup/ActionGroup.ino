// Action groups are supported by both the xArm and LeArm.
// actionIsRunning is not supported by LeArm or SoftwareSerial.
#include <xArmServoController.h>

xArmServoController myArm = xArmServoController(xArm, Serial1);

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  while(!Serial) {} // Wait for terminal to open.

  Serial.println("\r\nAction groups are supported by both the xArm and LeArm.");
  Serial.println("actionIsRunning is not supported by LeArm or SoftwareSerial.");
  Serial.println("Create an action group and save it to the xArm as Action Group 0.");
  Serial.println("\r\nPress any key when ready.");
  while (!Serial.available()) {}
  Serial.flush();

  myArm.actionRun(0);
  Serial.println("\r\nAction Group 0 is running. Waiting for end.");
}

// actionIsRunning() must be used within a loop in order for serial activity
// to be detected.
void loop() {
  if (!myArm.actionIsRunning()) {
    Serial.println("Action Group 0 has ended.");
    while(true) {} // loop here indefinately.
  }
}

// This serial event  listener is necessary in order for xArmServoController
// to detect activity from the xArm. The xArmServoController serialEvent
// will return true when the Action Group end has occured.
void serialEvent1() {
  if (myArm.serialEvent()) {
    Serial.println("BEEP BEEP: serialEvent1 detected Action Group 0 has ended.");
    myArm.beep();
  }
}
