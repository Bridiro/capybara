#include "Map.h"
#include "Tof.h"
#include "Motors.h"
#include "Movements.h"
#include "Exploration.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

void setup()
{
  Serial.begin(115200);

  Serial.println("Configurazione iniziata");

  Serial.println("Inizializzazione DISPLAY");
  initScreen();
  printlnScreen("DISPLAY: DONE");

  Serial.println("Inizializzazione IMU");
  initGyro();
  printlnScreen("IMU: DONE");

  Serial.println("Calibrazione IMU, non muovere il robot!");
  calibrateGyro(500);
  printlnScreen("IMU: CALIBRATED");

  Serial.println("Inizializzazione motori");
  initMotor();
  printlnScreen("MOTORS: DONE");

  Serial.println("Inizializzazione encoder");
  initEncoder();
  printlnScreen("ENCODERS: DONE");

  Serial.println("Inizializzazione TOF");
  initTof();
  printlnScreen("TOF: DONE");

  Serial.println("Inizializzazione mappa");
  m.init();
  printlnScreen("MAP: DONE");

  Serial.println("Setup completo!");
  printlnScreen("COMPLETED!");

  delay(3000);

  explore();
}

void loop()
{
  straightForCm(30, 170);
  delay(500);
  rotateForDegree(90, 210);
  delay(500);
  straightForCm(30, 170);
  delay(500);
  rotateForDegree(90, 210);
  delay(500);
  straightForCm(30, 170);
  delay(500);
  rotateForDegree(90, 210);
  delay(500);
  straightForCm(30, 170);
  delay(500);
  rotateForDegree(90, 210);
  delay(5000);
}
