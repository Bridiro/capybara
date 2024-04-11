#include "Motors.h"

void initMotor()
{
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);

  motorStop();
  motorSetSpeedBoth(170);
}

void motorSetSpeedA(uint8_t vel)
{
  pwmA = vel * MULTIPLIER_A;
}

void motorSetSpeedB(uint8_t vel)
{
  pwmB = vel * MULTIPLIER_B;
}

void motorSetSpeedBoth(uint8_t vel)
{
  motorSetSpeedA(vel);
  motorSetSpeedB(vel);
}

void motorLeft()
{
  analogWrite(INA1, 0);
  analogWrite(INA2, pwmA);

  analogWrite(INB1, pwmB);
  analogWrite(INB2, 0);
}

void motorRight()
{
  analogWrite(INA1, pwmA);
  analogWrite(INA2, 0);

  analogWrite(INB1, 0);
  analogWrite(INB2, pwmB);
}

void motorBackward()
{
  analogWrite(INA1, 0);
  analogWrite(INA2, pwmA);

  analogWrite(INB1, 0);
  analogWrite(INB2, pwmB);
}

void motorStraight()
{
  analogWrite(INA1, pwmA);
  analogWrite(INA2, 0);

  analogWrite(INB1, pwmB);
  analogWrite(INB2, 0);
}

void motorStop()
{
  analogWrite(INA1, 0);
  analogWrite(INA2, 0);

  analogWrite(INB1, 0);
  analogWrite(INB2, 0);
}

void motorBreak()
{
  analogWrite(INA1, 255);
  analogWrite(INA2, 255);

  analogWrite(INB1, 255);
  analogWrite(INB2, 255);
}
