#include "Tof.h"


/**
 * @brief Init tofs @endif
 * 
 */
void initTof() {
  I2CMultiplexer.begin();
  for(int i=0; i<8; i++) {
    I2CMultiplexer.selectPort(i);
    while(!(VL6180X.begin())){
      delay(500);
    }
  }
}


/**
 * @brief Read the selected tof value @endif
 * 
 * @param t From 0 to 7
 * @return uint8_t 
 */
uint8_t readTof(uint8_t t) {
  I2CMultiplexer.selectPort(t);
  return VL6180X.rangePollMeasurement();
}


/**
 * @brief Get the Muri object
 * 
 * @return boolean[] Norh East South West
 */
boolean* getMuri() {
  boolean* muri;
  for(int i=0; i<4; i++) {
    *muri[i] = false;
  }
  I2CMultiplexer.selectPort(0);
  uint8_t m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(1);
  uint8_t m2 = VL6180X.rangePollMeasurement();
  if(m < 100 && m2 < 100) {
    *muri[0] = true;
  }
  I2CMultiplexer.selectPort(2);
  m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(3);
  m2 = VL6180X.rangePollMeasurement();
  if(m < 100 && m2 < 100) {
    *muri[1] = true;
  }
  I2CMultiplexer.selectPort(4);
  m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(5);
  m2 = VL6180X.rangePollMeasurement();
  if(m < 100 && m2 < 100) {
    *muri[2] = true;
  }
  I2CMultiplexer.selectPort(6);
  m = VL6180X.rangePollMeasurement();
  I2CMultiplexer.selectPort(7);
  m2 = VL6180X.rangePollMeasurement();
  if(m < 100 && m2 < 100) {
    *muri[3] = true;
  }
  return muri;
}