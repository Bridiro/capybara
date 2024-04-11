#ifndef Motors_h
#define Motors_h

#include <Arduino.h>

#define INA1 2
#define INA2 3
#define INB1 5
#define INB2 4

#define MULTIPLIER_A 1
#define MULTIPLIER_B 1

static uint8_t pwmA;
static uint8_t pwmB;

void initMotor();

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