#include "Exploration.h"


/**
 * @brief Main function that start the exploration @endif
 * 
 */
void explore() {
  while(true) {
    bool front = frontWall();
    bool right = rightWall();
    bool left = leftWall();
    bool back = backWall();

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
      straightForCm(30, 170);
      m.straight();
    }
    else if(dir == 0) {
      rotateForDegree(90, 210);
      m.turnRight();
    }
    else if(dir == 2) {
      rotateForDegree(-90, 210);
      m.turnLeft();
    }
    else if(dir == 3) {
      rotateForDegree(180, 210);
      m.turn180();
    }
    else if(dir == 4) {
      break;
    }
    
    clearScreen();
    printlnScreen(dir);
    m.printMap();
    delay(300);
  }
}