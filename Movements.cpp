#include "Movements.h"


/**
 * @brief Init screen @endif
 * 
 */
void initScreen() {
  if(!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("DISPLAY NON VA!");
    for(;;);
  }

  lcd.display();
  delay(200);
  lcd.clearDisplay();
  lcd.display();
  lcd.setTextColor(WHITE);
  lcd.setTextSize(1);
}


/**
 * @brief Init IMU @endif
 * 
 */
void initGyro() {
  if(!IMU.begin()) {
    Serial.println("IMU NON VA!");
    for(;;);
  }
}


/**
 * @brief Init encoder pins and attach the interrupt @endif
 * 
 */
void initEncoder() {
  pinMode(ENCA, INPUT);
  pinMode(ENCB, INPUT);

  attachInterrupt(digitalPinToInterrupt(ENCA), readEncoder, RISING);
}


/**
 * @brief Straight for CM @endif
 * 
 * @param cm Centimeters to move
 * @param pwm PWM value
 */
void straightForCm(float cm, int pwm) {
  if(pwm > 255) {
    pwm = 255;
  }
  motorSetSpeedBoth(pwm);

  int target = calculateStep(cm);
  enc = 0;
  float x, y, z;
  float zTot = 0;
  float counterZ;
  int count=0;
  counterZ = z;

  while(enc < target) {
    if(IMU.gyroscopeAvailable()) {
      if(count % 5 == 0) {
        IMU.readGyroscope(x, y, counterZ);
      }
      count++;
      IMU.readGyroscope(x, y, z);
      
      zTot += (z-counterZ);

      if(zTot > 0) {
        motorSetSpeedA(pwm + (zTot / 3));
        motorSetSpeedB(pwm);
      }
      else if(zTot < 0) {
        motorSetSpeedB(pwm + (zTot / 3));
        motorSetSpeedA(pwm);
      }
      else {
        motorSetSpeedBoth(pwm);
      }
    }
    lcd.clearDisplay();
    lcd.setCursor(1, 1);
    lcd.println(enc);
    lcd.println(target);
    lcd.print(zTot);
    lcd.display();
    motorStraight();
  }

  motorStop();
  enc = 0;
}


/**
 * @brief Backwards for CM @endif
 * 
 * @param cm Centimeters to move
 * @param pwm PWM value
 */
void backForCm(float cm, int pwm) {
  if(pwm > 255) {
    pwm = 255;
  }
  motorSetSpeedBoth(pwm);

  int target = calculateStep(-cm);
  enc = 0;
  float x, y, z;
  float zTot = 0;
  float counterZ;
  int count=0;
  counterZ = z;

  while(target < enc) {
    if(IMU.gyroscopeAvailable()) {
      if(count % 10 == 0) {
        IMU.readGyroscope(x, y, counterZ);
      }
      count++;
      IMU.readGyroscope(x, y, z);
      
      zTot += (z-counterZ);

      if(zTot > 0) {
        motorSetSpeedA(pwm + (zTot / 3));
        motorSetSpeedB(pwm);
      }
      else if(zTot < 0) {
        motorSetSpeedB(pwm + (zTot / 3));
        motorSetSpeedA(pwm);
      }
      else {
        motorSetSpeedBoth(pwm);
      }
    }
    lcd.clearDisplay();
    lcd.setCursor(1, 1);
    lcd.println(enc);
    lcd.println(target);
    lcd.print(zTot);
    lcd.display();
    motorBackward();
  }

  motorStop();
  enc = 0;
}


/**
 * @brief Rotate the robot for degree @endif
 * 
 * @param degree Degree value to turn
 * @param pwm PWM value
 */
void rotateForDegree(float degree, int pwm) {
  if(pwm > 255) {
    pwm = 255;
  }
  motorSetSpeedBoth(pwm);

  float target = calculateGyro(degree);
  float x, y, z;
  float zTot = 0;

  //destra
  if(target < 0) {
    target *= 0.915;
    while(zTot > target) {
      if(IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);
        zTot += (z-(gyroOffsetZ*0.7));
      }
      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.println(target);
      lcd.println(zTot);
      lcd.print(gyroOffsetZ);
      lcd.display();
      motorRight();
    }

    motorStop();
  }
  //sinistra
  else if(target > 0) {
    while(zTot < target) {
      if(IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);
        zTot += (z-gyroOffsetZ);
      }
      lcd.clearDisplay();
      lcd.setCursor(1, 1);
      lcd.println(target);
      lcd.println(zTot);
      lcd.print(gyroOffsetZ);
      lcd.display();
      motorLeft();
    }

    motorStop();
  }
  else {
    motorStop();
  }
}


/**
 * @brief calibrate the IMU @endif
 * 
 * @param n 
 */
void calibrateGyro(int n) {
  float x, y, z;

  gyroOffsetX = 0;
  gyroOffsetY = 0;
  gyroOffsetZ = 0;
  
  int i = 0;
  while (i < n)
  {
    if (IMU.gyroscopeAvailable()) {
      IMU.readGyroscope(x, y, z);
      gyroOffsetX -= x;
      gyroOffsetY -= y;
      gyroOffsetZ -= z;
      i++;
    }
  }

  gyroOffsetX /= n;
  gyroOffsetY /= n;
  gyroOffsetZ /= n;
}


/**
 * @brief Calculate steps to make to travel cm @endif
 * 
 * @param cm Centimeters to convert
 */
int calculateStep(float cm) {
  return cm / (6.15*PI) * 12000 * 0.85;
}


/**
 * @brief Calculate gyro to rotate degrees @endif
 * 
 * @param degree Degrees to rotate
 * @return float value of gyro
 */
float calculateGyro(float degree) {
  return -(degree * 7000 / 360);
}


/**
 * @brief Function to read encoder @endif
 * 
 */
void readEncoder() {
  int b = digitalRead(ENCB);
  if(b>0){
    enc -= 1;
  }
  else{
    enc += 1;
  }
}


/**
 * @brief Print on lcd @endif
 * 
 * @param s char array to print
 */
void printlnScreen(char *s) {
  lcd.println(s);
  lcd.display();
}


/**
 * @brief Print on lcd @endif
 * 
 * @param n int to print
 */
void printlnScreen(int n) {
  lcd.println(n);
  lcd.display();
}


/**
 * @brief Clear the lcd @endif
 * 
 */
void clearScreen() {
  lcd.clearDisplay();
  lcd.display();
}
