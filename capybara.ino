#include "Map.h"
#include "Motors.h"
#include "Movements.h"

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>

#define WIDTH 128
#define HEIGHT 64

#define RESET -1

Adafruit_SSD1306 lcd(WIDTH, HEIGHT, &Wire, RESET);

float x, y, z;

void setup() {
  Serial.begin(115200);

  Serial.println("Configurazione iniziata");

  Serial.println("Inizializzazione IMU");
  if(!IMU.begin()) {
    Serial.println("IMU NON VA!");
    for(;;);
  }
  Serial.println("Calibrazione IMU, non muovere il robot!");
  calibrateGyro(500);

  Serial.println("Inizializzazione DYSPLAY");
  initScreen(lcd);

  Serial.println("Inizializzazione motori");
  motorInit();

  Serial.println("Inizializzazione encoder");
  initEncoder();
  
  Serial.println("Setup completo!");

  delay(2000);
}

void loop() {
  straightForCm(50, 170);
  delay(500);
  rotateForDegree(90, 230);
  delay(500);
  straightForCm(30, 170);
  delay(500);
  rotateForDegree(-90, 230);
  delay(500);
  backForCm(50, 170);

  lcd.clearDisplay();
  lcd.println("FINITOOO!");
  lcd.display();
  delay(5000);
}
