#include "Motors.h"

void motorInit() {
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(INB1, OUTPUT);
  pinMode(INB2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  motorStop();
  motorSetSpeedBoth(160);
}

void motorSetSpeedA(uint8_t vel) {
  analogWrite(PWMA, vel * MULTIPLIER_A);
}

void motorSetSpeedB(uint8_t vel) {
  analogWrite(PWMB, vel * MULTIPLIER_B);
}

void motorSetSpeedBoth(uint8_t vel) {
  motorSetSpeedA(vel);
  motorSetSpeedB(vel);
}

void motorLeft() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);

  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}

void motorRight() {
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}

void motorBackward() {
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, LOW);
}

void motorStraight() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);

  digitalWrite(INB1, LOW);
  digitalWrite(INB2, HIGH);
}

void motorStop() {
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);

  digitalWrite(INB1, LOW);
  digitalWrite(INB2, LOW);
}

void motorBreak() {
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, HIGH);

  digitalWrite(INB1, HIGH);
  digitalWrite(INB2, HIGH);
}