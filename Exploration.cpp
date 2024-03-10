#include "Exploration.h"


/**
 * @brief Main function that start the exploration @endif
 * 
 */
void explore() {
  while(true) {
    bool front = frontWall();
    delay(150);
    bool right = rightWall();
    delay(150);
    bool left = leftWall();
    delay(150);
    bool back = backWall();

    Serial.println(m.dir);
    Serial.print(front);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" ");
    Serial.print(left);
    Serial.print(" ");
    Serial.println(back);

    if(m.dir == 1) {
      m.scanNeighbors(front, right, back, left);
    }
    else if(m.dir == 0) {
      m.scanNeighbors(left, front, right, back);
    }
    else if(m.dir == 2) {
      m.scanNeighbors(right, back, left, front);
    }
    else if(m.dir == 3) {
      m.scanNeighbors(back, left, front, right);
    }

    int dir = m.suggestDirection();

    if(dir == 1) {
      clearScreen();
      printlnScreen("DRITTO");
      delay(1000);
      clearScreen();
      straightForCm(30, 170);

      if(calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if(dir == 0) {
      clearScreen();
      printlnScreen("DESTRA");
      delay(1000);
      clearScreen();
      rotateForDegree(90, 210);
      m.turnRight();
      delay(150);
      straightForCm(30, 170);
      
      if(calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if(dir == 2) {
      clearScreen();
      printlnScreen("SINISTRA");
      delay(1000);
      clearScreen();
      rotateForDegree(-90, 210);
      m.turnLeft();
      delay(150);
      straightForCm(30, 170);
      
      if(calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if(dir == 3) {
      clearScreen();
      printlnScreen("DIETRO");
      delay(1000);
      clearScreen();
      rotateForDegree(90, 210);
      rotateForDegree(90, 210);
      m.turn180();
      delay(150);
      straightForCm(30, 170);
      
      if(calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if(dir == 4) {
      Serial.println("FINITOOOOO");
      clearScreen();
      printlnScreen("FINITOOOO");
      for(;;);
    }

    m.printMap();
    delay(300);
  }
}