/*
  xArmServoController.cpp - Library for controlling xArm servos.
  Version 1.0.0
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/

#include "xArmServoController.h"

xArmServoController::xArmServoController(xArmMode mode, Stream &serial_port) : serial_port(serial_port) {
  xMode = mode;
}

/*** Send, Recv and checkServoLimits ***/

void xArmServoController::send(int cmd, int len = 0)
{
  serial_port.flush();
  serial_port.write(SIGNATURE);
  serial_port.write(SIGNATURE);
  serial_port.write(len + 2);
  serial_port.write(cmd);
  if (len > 0) {
    serial_port.write(_buffer, len);
  }
}

int xArmServoController::recv(int cmd)
{
  if (-1 != serial_port.readBytes(_buffer, 4)) {
    if (_buffer[0] == SIGNATURE && _buffer[1] == SIGNATURE && _buffer[3] == cmd) {
      int len = _buffer[2] - 2;
      return serial_port.readBytes(_buffer, len);
    }
  }
  return -1;
}

unsigned xArmServoController::clamp(unsigned v, unsigned lo, unsigned hi) {
    return (v < lo) ? lo : (hi < v) ? hi : v;
}

unsigned xArmServoController::clampServoLimits(int servo, unsigned value) {
  switch (xMode)
  {
    case xArm:
      return clamp(value, 0, 1000);
    case LeArm:
      if(servo == 1) {
        return clamp(value, 1500, 2500);
      } else {
        return clamp(value, 500, 2500);
      }
    default:
      return value;
  }
}

/*** SetPosition ***/

void xArmServoController::setPosition(int servo_id, unsigned position, unsigned duration = 1000, bool wait = false)
{
  position = clampServoLimits(servo_id, position);
  _buffer[0] = 1;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  _buffer[3] = servo_id;
  _buffer[4] = lowByte(position);
  _buffer[5] = highByte(position);
  send(CMD_SERVO_MOVE, 6);
  if (wait) {
    delay(duration);
  }
}

void xArmServoController::setPosition(xArmServo servo, unsigned duration = 1000, bool wait = false)
{
  setPosition(servo.servo_id, servo.position, duration, wait);
}

void xArmServoController::setPosition(xArmServo servos[], int count, unsigned duration = 1000, bool wait = false)
{
  int len = count * 3 + 3;
  _buffer[0] = count;
  _buffer[1] = lowByte(duration);
  _buffer[2] = highByte(duration);
  for (int i = 3, j = 0; j < count; i += 3, j++) {
    _buffer[i] = servos[j].servo_id;
    _buffer[i + 1] = lowByte(servos[j].position);
    _buffer[i + 2] = highByte(servos[j].position);
  }
  send(CMD_SERVO_MOVE, len);
  if (wait) {
    delay(duration);
  }
}

/*** GetPosition ***/

int xArmServoController::getPosition(int servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_GET_SERVO_POSITION, 2);
  if (-1 != recv(CMD_GET_SERVO_POSITION)) {
    return _buffer[3] * 256 + _buffer[2];
  }
  return -1;
}

int xArmServoController::getPosition(xArmServo &servo)
{
  int pos = getPosition(servo.servo_id);
  servo.position = pos;
  return pos;
}

bool xArmServoController::getPosition(xArmServo servos[], int count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_GET_SERVO_POSITION, count + 1);
  // servo positions returned are in the same order sent.
  if (-1 != recv(CMD_GET_SERVO_POSITION)) {
    for (int i = 2, j = 0; j < count; i += 3, j++) {
      servos[j].position = _buffer[i + 1] * 256 + _buffer[i];
    }
    return true;
  }
  return false;
}

/*** Off ***/

void xArmServoController::servoOff(int servo_id)
{
  _buffer[0] = 1;
  _buffer[1] = servo_id;
  send(CMD_SERVO_STOP, 2);
}

void xArmServoController::servoOff(int num, int servo_id, ...)
{
  _buffer[0] = num;
  _buffer[1] = servo_id;  
  if (num > 1) {
    va_list args;
    va_start(args, servo_id);
    for (int i = 2; i <= num; i++) {
      _buffer[i] = (byte)va_arg(args, int);
    }
    va_end(args);    
  }
  send(CMD_SERVO_STOP, num + 1);
}

void xArmServoController::servoOff(xArmServo servo)
{
  servoOff(servo.servo_id);
}

void xArmServoController::servoOff(xArmServo servos[], int count)
{
  _buffer[0] = count;
  for (int i = 1, j = 0; j < count; i++, j++) {
    _buffer[i] = servos[j].servo_id;
  }
  send(CMD_SERVO_STOP, count + 1);
}

void xArmServoController::servoOff()
{
  _buffer[0] = 6;
  _buffer[1] = 1;
  _buffer[2] = 2;
  _buffer[3] = 3;
  _buffer[4] = 4;
  _buffer[5] = 5;
  _buffer[6] = 6;
  send(CMD_SERVO_STOP, 7);
}

/*** Action Group ***/

  void xArmServoController::actionRun(int group, unsigned times = 1) {
    _buffer[0] = group;
    _buffer[1] = lowByte(times);
    _buffer[2] = highByte(times);
    send(CMD_ACTION_GROUP_RUN, 3);
    actionRunning = true;
  }

  void xArmServoController::actionStop() {
    send(CMD_ACTION_GROUP_STOP, 0);
  }

  void xArmServoController::actionSpeed(int group, unsigned percent) {
    _buffer[0] = group;
    _buffer[1] = lowByte(percent);
    _buffer[2] = highByte(percent);
    bool _actionRunning = actionRunning;
    send(CMD_ACTION_GROUP_SPEED, 3);
    actionRunning = _actionRunning;
  }

  bool xArmServoController::actionIsRunning() {
    return actionRunning;
  }

  bool xArmServoController::serialEvent() {
    if (actionRunning) {
      if (-1 != serial_port.readBytes(_buffer, 4)) {
        if (_buffer[0] == SIGNATURE && _buffer[1] == SIGNATURE) {
          switch (_buffer[3])
          {
          case CMD_ACTION_GROUP_STOP:
          case CMD_ACTION_GROUP_END:
            actionRunning = false;
            return true;
          default:
            break;
          }
        }
      }
    }
    return false;
  }

/*** GetBatteryVoltage ***/

int xArmServoController::getBatteryVoltage()
{
  send(CMD_GET_BATTERY_VOLTAGE);
  if (-1 != recv(CMD_GET_BATTERY_VOLTAGE)) {
    return _buffer[1] * 256 + _buffer[0];
  }
  return -1;
}

void xArmServoController::beep() {
  serial_port.write((byte)CMD_BEEP);
}