#ifndef Motors_h
#define Motors_h

#include <Arduino.h>

#define PWMA 13
#define INA2 12
#define INA1 11
#define INB1 9
#define INB2 10
#define PWMB 8

#define MULTIPLIER_A 1
#define MULTIPLIER_B 1.2

void motorInit();

void motorSetSpeedA(uint8_t vel);
void motorSetSpeedB(uint8_t vel);
void motorSetSpeedBoth(uint8_t vel);

void motorLeft();
void motorRight();
void motorBackward();
void motorStraight();
void motorStop();
void motorBreak();

#endif