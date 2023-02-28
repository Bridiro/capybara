#ifndef Tof_h
#define Tof_h

#include <Arduino.h>
#include <DFRobot_VL6180X.h>
#include <Wire.h>
#include <DFRobot_I2C_Multiplexer.h>

static DFRobot_I2C_Multiplexer I2CMultiplexer(&Wire, 0x70);
static DFRobot_VL6180X VL6180X;

void initTof();
uint8_t readTof(uint8_t t);
boolean* getMuri();

#endif
