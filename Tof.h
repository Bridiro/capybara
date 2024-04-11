#ifndef Tof_h
#define Tof_h

#include <Arduino.h>
#include <DFRobot_VL6180X.h>
#include <Wire.h>
#include <DFRobot_I2C_Multiplexer.h>

#define FRONT_TOF_INDEX 1
#define RIGHT_FRONT_TOF_INDEX 2
#define RIGHT_BACK_TOF_INDEX 3
#define LEFT_FRONT_TOF_INDEX 0
#define LEFT_BACK_TOF_INDEX 5
#define BACK_TOF_INDEX 4

static DFRobot_I2C_Multiplexer I2CMultiplexer(&Wire, 0x70);
static DFRobot_VL6180X VL6180X;

void initTof();
uint8_t readTof(uint8_t t);
bool frontWall();
bool rightWall();
bool leftWall();
bool backWall();

#endif
