/*
  xArmServoController.h - Library for controlling xArm servos.
  Version 1.0.0
  Created by Chris Courson, July 9, 2020.
  Released into the public domain.
*/
#pragma once
#ifndef XARMSERVOCONTROLLER_H
#define XARMSERVOCONTROLLER_H

#include <stdarg.h>
#include <Arduino.h>

#define SIGNATURE               0x55
#define CMD_BEEP                0x00
#define CMD_SERVO_MOVE          0x03
#define CMD_ACTION_GROUP_RUN    0x06
#define CMD_ACTION_GROUP_STOP   0x07
#define CMD_ACTION_GROUP_END    0x08
#define CMD_ACTION_GROUP_SPEED  0x0B
#define CMD_GET_BATTERY_VOLTAGE 0x0f
#define CMD_SERVO_STOP          0x14
#define CMD_GET_SERVO_POSITION  0x15

enum xArmMode : int {xArm, LeArm};

struct xArmServo {
    int servo_id;
    unsigned position;
};

class xArmServoController {
  public:  
    xArmServoController(xArmMode mode, Stream &serial_port);

    void setPosition(int servo_id, unsigned position, unsigned duration = 1000, bool wait = false);
    void setPosition(xArmServo servo, unsigned duration = 1000, bool wait = false);
    void setPosition(xArmServo servos[], int count, unsigned duration = 1000, bool wait = false);

    int getPosition(int servo_id);
    int getPosition(xArmServo &servo);
    bool getPosition(xArmServo servos[], int count);
    
    void servoOff(int servo_id);
    void servoOff(int num, int servo_id, ...);
    void servoOff(xArmServo servo);
    void servoOff(xArmServo servos[], int count);
    void servoOff();

    void actionRun(int group, unsigned times = 1);
    void actionStop();
    void actionSpeed(int group, unsigned percent);
    bool actionIsRunning();
    bool serialEvent();

    int getBatteryVoltage();
    
    void beep();

  protected:
    Stream &serial_port;
  
  private:
    byte _buffer[32];
    xArmMode xMode;

    bool actionRunning;
    
    unsigned clamp(unsigned v, unsigned lo, unsigned hi);
    unsigned clampServoLimits(int servo, unsigned value);
    void send(int cmd, int len);
    int recv(int cmd);
};

#endif
