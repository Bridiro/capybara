#ifndef Movements_h
#define Movements_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino_LSM9DS1.h>

#define ENCA 6
#define ENCB 7

static Adafruit_SSD1306 lcd1;

static int enc;

static float gyroOffsetX;
static float gyroOffsetY;
static float gyroOffsetZ;

void initScreen(Adafruit_SSD1306 lcda);
void initEncoder();
void straightForCm(float cm, int pwm);
void backForCm(float cm, int pwm);
void rotateForDegree(float degree, int pwm);
int calculateStep(float cm);
void calibrateGyro(int n);
void readEncoder();

#endif
