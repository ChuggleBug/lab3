#include <Arduino.h>
#include <SparkFunLSM6DSO.h>

#include "main.h"
#include "app_config.h"
#include "ble_svc.h"

LSM6DSO myIMU;

#define STEP_THRESHOLD_G  (0.25)
#define STEP_DELAY_MS     (300)

unsigned long lastStepTime = 0;
int stepCount = 0;

void setup() {
  Serial.begin(BAUD_RATE);

  Wire.begin();
  delay(10);
  if (myIMU.begin()) {
    Serial.println("Ready.");
  } else {
    Serial.println("Could not connect to IMU.");
    Serial.println("Freezing");
  }

  if (myIMU.initialize(BASIC_SETTINGS)) {
    Serial.println("Loaded Settings.");
  }

  while (!Serial)
    ;

  Serial.println("Initializing BLE service...");
  app_ble_svc_init();
}

void loop() {
  float ax = myIMU.readFloatAccelX();
  float ay = myIMU.readFloatAccelY();
  float az = myIMU.readFloatAccelZ();

  // Compute magnitude of acceleration (ignoring gravity)
  float magnitude = sqrt(ax * ax + ay * ay + az * az);
  float filtered = fabs(magnitude - 1.0);

  unsigned long currentTime = millis();
  if (filtered > STEP_THRESHOLD_G && (currentTime - lastStepTime) > STEP_DELAY_MS) {
    stepCount++;
    lastStepTime = currentTime;
    Serial.print("Step detected! Total steps: ");
    Serial.println(stepCount);
  }

  delay(20);
}