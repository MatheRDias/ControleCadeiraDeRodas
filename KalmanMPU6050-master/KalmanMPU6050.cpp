#include "KalmanMPU6050.h"
#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22

#define IMU_ADDR 0x68
#define IMU_ACCEL_XOUT_H 0x3B
#define IMU_REG 0x19
#define IMU_PWR_MGMT_1 0x6B

#define RAD_TO_DEG (180.0 / 3.14159265359)

#define sqr(x) ((x)*(x))
#define hypotenuse(x, y) sqrt(sqr(x) + sqr(y))

typedef struct {
  float Q_angle;
  float Q_bias;
  float R_measure;

  float angle;
  float bias;
  float rate;

  float P[2][2];
  float K[2];
  float y;
  float S;
} Kalman;

static Kalman kalmanX;
static Kalman kalmanY;

static float gyroXAngle, gyroYAngle;

uint32_t IMU::lastProcessed = 0;

int16_t IMU::accelX, IMU::accelY, IMU::accelZ;
int16_t IMU::gyroX, IMU::gyroY, IMU::gyroZ;

float IMU::kalXAngle, IMU::kalYAngle;

void Kalman_Init(Kalman *k) {
  k->Q_angle = 0.001f;
  k->Q_bias = 0.003f;
  k->R_measure = 0.03f;

  k->angle = 0;
  k->bias = 0;

  k->P[0][0] = 0;
  k->P[0][1] = 0;
  k->P[1][0] = 0;
  k->P[1][1] = 0;
}

float Kalman_GetAngle(Kalman *k, float newAngle, float newRate, float dt) {
  k->rate = newRate - k->bias;
  k->angle += dt * k->rate;

  k->P[0][0] += dt * (dt*k->P[1][1] - k->P[0][1] - k->P[1][0] + k->Q_angle);
  k->P[0][1] -= dt * k->P[1][1];
  k->P[1][0] -= dt * k->P[1][1];
  k->P[1][1] += k->Q_bias * dt;

  k->S = k->P[0][0] + k->R_measure;
  k->K[0] = k->P[0][0] / k->S;
  k->K[1] = k->P[1][0] / k->S;

  k->y = newAngle - k->angle;
  k->angle += k->K[0] * k->y;
  k->bias  += k->K[1] * k->y;

  k->P[0][0] -= k->K[0] * k->P[0][0];
  k->P[0][1] -= k->K[0] * k->P[0][1];
  k->P[1][0] -= k->K[1] * k->P[0][0];
  k->P[1][1] -= k->K[1] * k->P[0][1];

  return k->angle;
}

void IMU::init() {
  Serial.begin(115200);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(400000);

  Wire.beginTransmission(IMU_ADDR);
  Wire.write(IMU_REG);
  Wire.write(7);
  Wire.write(0); Wire.write(0); Wire.write(0);
  Wire.endTransmission();

  Wire.beginTransmission(IMU_ADDR);
  Wire.write(IMU_PWR_MGMT_1);
  Wire.write(0x01);
  Wire.endTransmission();

  delay(100);

  Kalman_Init(&kalmanX);
  Kalman_Init(&kalmanY);

  MPU6050Read();

  float roll, pitch;
  RollPitchFromAccel(&roll, &pitch);

  kalmanX.angle = roll;
  kalmanY.angle = pitch;
  gyroXAngle = roll;
  gyroYAngle = pitch;

  lastProcessed = micros();
}

void IMU::read() {
  float dt = (micros() - lastProcessed) / 1000000.0f;
  lastProcessed = micros();

  MPU6050Read();

  float roll, pitch;
  RollPitchFromAccel(&roll, &pitch);

  float gyroXRate = gyroX / 131.0f;
  float gyroYRate = gyroY / 131.0f;

  kalXAngle = Kalman_GetAngle(&kalmanX, roll, gyroXRate, dt);
  kalYAngle = Kalman_GetAngle(&kalmanY, pitch, gyroYRate, dt);

  gyroXAngle += gyroXRate * dt;
  gyroYAngle += gyroYRate * dt;

  if (gyroXAngle < -180 || gyroXAngle > 180) gyroXAngle = kalXAngle;
  if (gyroYAngle < -180 || gyroYAngle > 180) gyroYAngle = kalYAngle;
}

float IMU::getRoll() { return kalXAngle; }
float IMU::getPitch() { return kalYAngle; }

int16_t IMU::getRawAccelX() { return accelX; }
int16_t IMU::getRawAccelY() { return accelY; }
int16_t IMU::getRawAccelZ() { return accelZ; }

int16_t IMU::getRawGyroX() { return gyroX; }
int16_t IMU::getRawGyroY() { return gyroY; }
int16_t IMU::getRawGyroZ() { return gyroZ; }

void IMU::MPU6050Read() {
  Wire.beginTransmission(IMU_ADDR);
  Wire.write(IMU_ACCEL_XOUT_H);
  Wire.endTransmission(false);
  Wire.requestFrom(IMU_ADDR, 14, true);

  accelX = Wire.read() << 8 | Wire.read();
  accelY = Wire.read() << 8 | Wire.read();
  accelZ = Wire.read() << 8 | Wire.read();
  Wire.read(); Wire.read();
  gyroX  = Wire.read() << 8 | Wire.read();
  gyroY  = Wire.read() << 8 | Wire.read();
  gyroZ  = Wire.read() << 8 | Wire.read();
}

void IMU::RollPitchFromAccel(float *roll, float *pitch) {
  *roll  = atan2((float)accelY, (float)accelZ) * RAD_TO_DEG;
  *pitch = atan(-(float)accelX / hypotenuse((float)accelY, (float)accelZ)) * RAD_TO_DEG;
}
