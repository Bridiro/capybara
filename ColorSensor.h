#ifndef ColorSensor_h
#define ColorSensor_h

#include <Arduino.h>
#include <tcs3200.h>

static uint8_t red, green, blue;

static tcs3200 tcs(12, 11, A2, A1, A3);

void calibrateBlue();
void calibrateBlack();
void calibrateCheckpoint();
boolean checkBlue();
boolean checkBlack();
boolean checkCheckpoint();

#endif