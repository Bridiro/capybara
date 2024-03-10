#include "Movements.h"

/**
 * @brief Init screen @endif
 *
 */
void initScreen()
{
    if (!lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    {
        Serial.println("DISPLAY NON VA!");
        for (;;)
            ;
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
void initGyro()
{
    if (!IMU.begin())
    {
        Serial.println("IMU NON VA!");
        for (;;)
            ;
    }
}

/**
 * @brief Init encoder pins and attach the interrupt @endif
 *
 */
void initEncoder()
{
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
void straightForCm(float cm, int pwm)
{
    enc = 0;
    float x, y, z;
    float zTot = 0;
    float counterZ;
    int count = 0;
    int target;

    float angleZ = 0;
    int newT;
    int oldT = millis();

    if (pwm > 255)
    {
        pwm = 255;
    }
    motorSetSpeedBoth(pwm);

    if (cm > 0)
    {
        target = calculateStep(cm);
    }
    else
    {
        target = calculateStep(-cm);
    }

    while (cm > 0 ? enc < target : target < enc)
    {
        if (IMU.gyroscopeAvailable())
        {
            newT = millis();
            float dt = (newT - oldT) * 1e-3;
            oldT = newT;

            IMU.readGyroscope(x, y, z);
            float gyroZ = z + gyroOffsetZ;
            angleZ += gyroZ * dt;
            Serial.println(angleZ);

            if (angleZ > 0)
            {
                motorSetSpeedA(pwm - angleZ * 2);
            }
            else if (angleZ < 0)
            {
                motorSetSpeedB(pwm - angleZ * 2);
            }
            else
            {
                motorSetSpeedBoth(pwm);
            }
        }
        lcd.clearDisplay();
        lcd.setCursor(1, 1);
        lcd.println(enc);
        lcd.println(target);
        lcd.print(zTot);
        lcd.display();
        if (cm > 0)
        {
            motorStraight();
        }
        else
        {
            motorBackward();
        }
    }

    motorStop();
}

/**
 * @brief Rotate the robot for degree @endif
 *
 * @param degree Degree value to turn
 * @param pwm PWM value
 */
void rotateForDegree(float degree, int pwm)
{
    if (pwm > 255)
    {
        pwm = 255;
    }
    motorSetSpeedBoth(pwm);

    float angleZ = 0;
    float x, y, z;
    int newT;
    int oldT = millis();

    if (degree > 0)
    {
        motorRight();
    }
    else
    {
        motorLeft();
    }

    while (degree > 0 ? angleZ * GYRO_MULTIPLIER_DX > -degree : angleZ * GYRO_MULTIPLIER_SX < -degree)
    {
        if (IMU.gyroscopeAvailable())
        {
            newT = millis();
            float dt = (newT - oldT) * 1e-3;
            oldT = newT;

            IMU.readGyroscope(x, y, z);
            float gyroZ = z + gyroOffsetZ;
            angleZ += gyroZ * dt;
            Serial.println(angleZ);
        }
    }

    motorStop();
}

/**
 * @brief calibrate the IMU @endif
 *
 * @param n
 */
void calibrateGyro(int n)
{
    float x, y, z;

    gyroOffsetX = 0;
    gyroOffsetY = 0;
    gyroOffsetZ = 0;

    int i = 0;
    while (i < n)
    {
        if (IMU.gyroscopeAvailable())
        {
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
int calculateStep(float cm)
{
    return cm / (6.15 * PI) * 12000 * 0.85;
}

/**
 * @brief Function to read encoder @endif
 *
 */
void readEncoder()
{
    int b = digitalRead(ENCB);
    if (b > 0)
    {
        enc -= 1;
    }
    else
    {
        enc += 1;
    }
}

/**
 * @brief Print on lcd @endif
 *
 * @param s char array to print
 */
void printlnScreen(char *s)
{
    lcd.println(s);
    lcd.display();
}

/**
 * @brief Print on lcd @endif
 *
 * @param n int to print
 */
void printlnScreen(int n)
{
    lcd.println(n);
    lcd.display();
}

/**
 * @brief Clear the lcd @endif
 *
 */
void clearScreen()
{
    lcd.clearDisplay();
    lcd.display();
}
