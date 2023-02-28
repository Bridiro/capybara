#include "Exploration.h"


/**
 * @brief Main function that start the exploration @endif
 * 
 */
void explore() {
  while(true) {
    boolean* muri = getMuri();
    Serial.println(*muri[0]);
    Serial.println(*muri[1]);
    Serial.println(*muri[2]);
    Serial.println(*muri[3]);
    m.scanNeighbors(*muri[0], *muri[1], *muri[2], *muri[3]);
    if(m.suggestDirection() == 4) {
      break;
    }
    m.printMap();
    delay(5000);
  }
}