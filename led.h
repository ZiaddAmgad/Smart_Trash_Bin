#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include "pico/stdlib.h"

#define RED_LED_PIN 13
#define GREEN_LED_PIN 14

void led_init();
void led_red_toggle(bool state);
void led_green_toggle(bool state);

#endif // LED_DRIVER_H