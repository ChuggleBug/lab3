#include <Arduino.h>

#include "app_config.h"
#include "ble_svc.h"

void setup() {
  Serial.begin(BAUD_RATE);

  while (!Serial);

  Serial.println("Initializing BLE service...");
  app_ble_svc_init();
}

void loop() {
  delay(1000);
}