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
  I2CMultiplexer.selectPort(0);
  uint8_t m = VL6180X.rangePollMeasurement();
  Serial.print("Front wall: ");
  Serial.println(m);

  return m < 200;
}


/**
 * @brief True if right wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool rightWall() {
  I2CMultiplexer.selectPort(1);
  uint8_t m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(2);
  uint8_t m2 = VL6180X.rangePollMeasurement();
  Serial.print("Right 1: ");
  Serial.println(m);
  Serial.print("Right 2: ");
  Serial.println(m2);

  return m < 210 && m2 < 210;
}


/**
 * @brief True if left wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool leftWall() {
  I2CMultiplexer.selectPort(3);
  uint8_t m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(4);
  uint8_t m2 = VL6180X.rangePollMeasurement();
  Serial.print("Left 1: ");
  Serial.println(m);
  Serial.print("Left 2: ");
  Serial.println(m2);

  return m < 210 && m2 < 210; 
}


/**
 * @brief True if back wall is present @endif
 * 
 * @return true 
 * @return false 
 */
bool backWall() {
  I2CMultiplexer.selectPort(5);
  uint8_t m = VL6180X.rangePollMeasurement();
  Serial.print("Back wall: ");
  Serial.println(m);

  return m < 160;
}
