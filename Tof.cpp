#include "Tof.h"


/**
 * @brief Init tofs @endif
 * 
 */
void initTof() {
  I2CMultiplexer.begin();
  for(int i=0; i<2; i++) {
    I2CMultiplexer.selectPort(i);
    while(!(VL6180X.begin())){
      delay(500);
    }
  }

  
}