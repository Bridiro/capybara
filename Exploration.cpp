#include "Exploration.h"

/**
 * @brief Main function that start the exploration @endif
 *
 */
void explore()
{
  while (true)
  {
    bool front = frontWall();
    printlnScreen("F: " + front ? "true" : "false");
    delay(150);
    bool right = rightWall();
    printlnScreen("R: " + right ? "true" : "false");
    delay(150);
    bool left = leftWall();
    printlnScreen("L: " + left ? "true" : "false");
    delay(150);
    bool back = backWall();
    printlnScreen("B: " + back ? "true" : "false");
    delay(2000);

    Serial.println(m.dir);
    Serial.print(front);
    Serial.print(" ");
    Serial.print(right);
    Serial.print(" ");
    Serial.print(left);
    Serial.print(" ");
    Serial.println(back);

    if (m.dir == 1)
    {
      m.scanNeighbors(front, right, back, left);
    }
    else if (m.dir == 0)
    {
      m.scanNeighbors(left, front, right, back);
    }
    else if (m.dir == 2)
    {
      m.scanNeighbors(right, back, left, front);
    }
    else if (m.dir == 3)
    {
      m.scanNeighbors(back, left, front, right);
    }

    int dir = m.suggestDirection();

    if (dir == 1)
    {
      clearScreen();
      printlnScreen("DRITTO");
      delay(1000);
      clearScreen();
      straightForCm(20, 100);

      if (calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if (dir == 0)
    {
      clearScreen();
      printlnScreen("DESTRA");
      delay(1000);
      clearScreen();
      rotateForDegree(52, 200);
      m.turnRight();
      delay(150);
      straightForCm(20, 100);

      if (calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if (dir == 2)
    {
      clearScreen();
      printlnScreen("SINISTRA");
      delay(1000);
      clearScreen();
      rotateForDegree(-65, 200);
      m.turnLeft();
      delay(150);
      straightForCm(20, 100);

      if (calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if (dir == 3)
    {
      clearScreen();
      printlnScreen("DIETRO");
      delay(1000);
      clearScreen();
      rotateForDegree(52, 200);
      rotateForDegree(52, 200);
      m.turn180();
      delay(150);
      straightForCm(20, 100);

      if (calculateStep(30) - calculateStep(10) < enc)
        m.straight();
    }
    else if (dir == 4)
    {
      Serial.println("FINITOOOOO");
      clearScreen();
      printlnScreen("FINITOOOO");
      for (;;)
        ;
    }

    m.printMap();
    delay(300);
  }
}