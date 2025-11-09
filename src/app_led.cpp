
#include <Arduino.h>

#include "app_led.h"
#include "app_config.h"

void app_led_init() {
    pinMode(LED_GPIO_NUM, OUTPUT);
}

void app_led_on() {
    digitalWrite(LED_GPIO_NUM, HIGH);
}

void app_led_off() {
    digitalWrite(LED_GPIO_NUM, LOW);
}
