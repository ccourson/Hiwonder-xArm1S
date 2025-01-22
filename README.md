# xArmServoController

Servo controller libraries for `Lewan-Soul`/`Lobot`/`Hiwonder` xArm1S and LeArm 6-DOF robotic arm.

* [Hiwonder-xArm1s is available here on Amazon.com](https://www.amazon.com/LewanSoul-Programmable-Feedback-Parameter-Programming/dp/B0793PFGCY).
* [LeArm is available here on Amazon.com](https://www.amazon.com/LewanSoul-Programmable-Feedback-Parameter-Programming/dp/B074T6DPKX)

Join the [LewanSoul-xArm Enthusiast group on Facebook](https://www.facebook.com/groups/xarm6dof).

## Table of Content

* [TTL Serial Control](#ttl-serial-control)
* [Arduino](https://github.com/ccourson/xArmServoController/tree/master/Arduino)
* [Python (Linux/MacOS/Windows)](https://github.com/ccourson/xArmServoController/tree/master/Python)
* [License](#license)

## TTL Serial Control

The control board mounted on the base of the xArm has a 4-pin connector which provides a signal path and power to an external host controller.

![xArm 6-DOF Robotic Arm](https://i.imgur.com/tG3Fw9u.jpg)

| Pin | Description
|-----|------------
| GND | Power and signal ground.
| TX  | Serial TTL signal from xArm to host controller. Mark = 5VDC, Space = 0VDC.
| RX  | - Serial TTL signal from host controller to xArm. Mark = 5VDC, Space = 0VDC.
| 5V  | 5 Volts DC power for eternal host controller. Current rating is not yet known. In most circumstances this is left unconnected.<br>`Warning: Do not connect to an external power source. Doing so will cause the xArm to beep loudly and may damage the control board.`

## License

[MIT Open Source Initiative](https://opensource.org/licenses/MIT)
