#ifndef Movements_h
#define Movements_h

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Arduino_LSM9DS1.h>

#include "Motors.h"

#define ENCA 6
#define ENCB 7

#define WIDTH 128
#define HEIGHT 64

#define RESET -1

static Adafruit_SSD1306 lcd(WIDTH, HEIGHT, &Wire, RESET);

static int enc;

static float gyroOffsetX;
static float gyroOffsetY;
static float gyroOffsetZ;

void initScreen();
void initGyro();
void initEncoder();
void straightForCm(float cm, int pwm);
void backForCm(float cm, int pwm);
void rotateForDegree(float degree, int pwm);
int calculateStep(float cm);
float calculateGyro(float degree);
void calibrateGyro(int n);
void readEncoder();
void printlnScreen(char *s);
void printlnScreen(int n);
void clearScreen();

#endif
