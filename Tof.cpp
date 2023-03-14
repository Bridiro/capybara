#include "Tof.h"


/**
 * @brief Init tofs @endif
 * 
 */
void initTof() {
  I2CMultiplexer.begin();
  for(int i=0; i<6; i++) {          // 0 front      1 2 right      3 4 left     5 back
    I2CMultiplexer.selectPort(i);
    while(!(VL6180X.begin())){
      delay(500);
    }
  }
}


/**
 * @brief Read the selected tof value @endif
 * 
 * @param t From 0 to 5
 * @return uint8_t 
 */
uint8_t readTof(uint8_t t) {
  I2CMultiplexer.selectPort(t);
  return VL6180X.rangePollMeasurement();
}


/**
 * @brief True if front wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool frontWall() {
  uint8_t m = readTof(0);

  if(m < 255) {
    return true;
  }
  return false;
}


/**
 * @brief True if right wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool rightWall() {
  uint8_t m = readTof(1);
  uint8_t m2 = readTof(2);

  if(m < 255 || m2 < 255) {
    return true;
  }
  return false;
}


/**
 * @brief True if left wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool leftWall() {
  uint8_t m = readTof(3);
  uint8_t m2 = readTof(4);

  if(m < 255 || m2 < 255) {
    return true;
  }
  return false;
}


/**
 * @brief True if back wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool backWall() {
  uint8_t m = readTof(5);

  if(m < 255) {
    return true;
  }
  return false;
}