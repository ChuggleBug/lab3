#include <Arduino.h>

#include "app_config.h"
#include "ble_svc.h"
#include "app_led.h"

void setup() {
  Serial.begin(BAUD_RATE);

  while (!Serial);

  Serial.println("Initializing LED...");
  app_led_init();

  Serial.println("Initializing BLE service...");
  app_ble_svc_init();
}

void loop() {
  delay(1000);
}