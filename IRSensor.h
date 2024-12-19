#ifndef IR_DRIVER_H
#define IR_DRIVER_H

#include "pico/stdlib.h"

#define IR_SENSOR_PIN 6
#define ONBOARD_LED_PIN 25
#define USER_LED_PIN 16

void ir_sensor_init();
bool ir_object_detected();

#endif // IR_DRIVER_H