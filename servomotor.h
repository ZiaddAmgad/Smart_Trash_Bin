#ifndef SERVO_DRIVER_H
#define SERVO_DRIVER_H

#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define SERVO_PIN 18
#define PWM_FREQUENCY 50
#define CLOCK_DIVIDER 64.0f
#define SERVO_MIN_US 1000
#define SERVO_MAX_US 2000
#define SERVO_MID_US 1500

void servo_init();
void servo_rotate(uint16_t pulse_width_us);
void servo_set_angle(float angle);
uint16_t servo_calculate_pwm_level(uint16_t pulse_width_us);

#endif // SERVO_DRIVER_H