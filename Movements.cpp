#include "Movements.h"
#include "Motors.h"


/**
 * @brief Init screen in Movements @endif
 * 
 * @param lcda Pointer to lcd object
 */
void initScreen(Adafruit_SSD1306 lcda) {
  lcd1 = lcda;
  if(!lcd1.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("DISPLAY NON VA!");
    for(;;);
  }
  lcd1.display();
  lcd1.clearDisplay();
  lcd1.display();
  lcd1.setTextColor(WHITE);
  lcd1.setTextSize(2);
}

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
    lcd1.clearDisplay();
    lcd1.setCursor(1, 1);
    lcd1.println(enc);
    lcd1.println(target);
    lcd1.print(zTot);
    lcd1.display();
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
    lcd1.clearDisplay();
    lcd1.setCursor(1, 1);
    lcd1.println(enc);
    lcd1.println(target);
    lcd1.print(zTot);
    lcd1.display();
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

  if(target < 0) {
    while(zTot > target) {
      if(IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);
        zTot += (z-(gyroOffsetZ*0.7));
      }
      lcd1.clearDisplay();
      lcd1.setCursor(1, 1);
      lcd1.println(target);
      lcd1.println(zTot);
      lcd1.print(gyroOffsetZ);
      lcd1.display();
      motorRight();
    }

    motorStop();
  }
  else if(target > 0) {
    while(zTot < target) {
      if(IMU.gyroscopeAvailable()) {
        IMU.readGyroscope(x, y, z);
        zTot += (z-gyroOffsetZ);
      }
      lcd1.clearDisplay();
      lcd1.setCursor(1, 1);
      lcd1.println(target);
      lcd1.println(zTot);
      lcd1.print(gyroOffsetZ);
      lcd1.display();
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
  return -(degree * 7500 / 360);
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
