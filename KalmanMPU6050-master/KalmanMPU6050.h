#ifndef KALMAN_MPU6050_H
#define KALMAN_MPU6050_H

#include <Arduino.h>

class IMU {
public:
  static void init();
  static void read();

  static float getRoll();
  static float getPitch();

  static int16_t getRawAccelX();
  static int16_t getRawAccelY();
  static int16_t getRawAccelZ();

  static int16_t getRawGyroX();
  static int16_t getRawGyroY();
  static int16_t getRawGyroZ();

private:
  static void MPU6050Read();
  static void RollPitchFromAccel(float *roll, float *pitch);

  static uint32_t lastProcessed;

  static int16_t accelX, accelY, accelZ;
  static int16_t gyroX, gyroY, gyroZ;

  static float kalXAngle;
  static float kalYAngle;
};

#endif
