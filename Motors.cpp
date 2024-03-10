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
  digitalWrite(INA1, LOW);
  analogWrite(INA2, pwmA);

  analogWrite(INB1, pwmB);
  digitalWrite(INB2, LOW);
}

void motorRight()
{
  analogWrite(INA1, pwmA);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, LOW);
  analogWrite(INB2, pwmB);
}

void motorBackward()
{
  digitalWrite(INA1, LOW);
  analogWrite(INA2, pwmA);

  digitalWrite(INB1, LOW);
  analogWrite(INB2, pwmB);
}

void motorStraight()
{
  analogWrite(INA1, pwmA);
  digitalWrite(INA2, LOW);

  analogWrite(INB1, pwmB);
  digitalWrite(INB2, LOW);
}

void motorStop()
{
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
}

void motorBreak()
{
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, HIGH);

  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, HIGH);
}
