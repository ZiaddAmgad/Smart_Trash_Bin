#ifndef ULTRASONIC_DRIVER_H
#define ULTRASONIC_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/timer.h"

#define TRIG_PIN 16
#define ECHO_PIN 17
#define MAX_DISTANCE_CM 400
#define TIMEOUT_US ((MAX_DISTANCE_CM * 2 * 1000000) / 343)

float ultrasonic_measure_distance();
void ultrasonic_init();
void ultrasonic_interpret_readings(float distance);
float ultrasonic_advanced_measurement();
uint64_t ultrasonic_get_pulse_duration();

#endif