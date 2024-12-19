#include "servomotor.h"

void servo_init() {
    gpio_set_function(SERVO_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(SERVO_PIN);

    pwm_config config = pwm_get_default_config();
    pwm_config_set_clkdiv(&config, CLOCK_DIVIDER);
    
    float div = CLOCK_DIVIDER;
    float sys_clk = 125000000;
    uint32_t wrap = (sys_clk / (PWM_FREQUENCY * div)) - 1;
    
    pwm_config_set_wrap(&config, wrap);
    pwm_init(slice_num, &config, true);

    servo_rotate(SERVO_MIN_US);
}

uint16_t servo_calculate_pwm_level(uint16_t pulse_width_us) {
    float div = CLOCK_DIVIDER;
    float sys_clk = 125000000;
    uint32_t wrap = (sys_clk / (PWM_FREQUENCY * div)) - 1;
    
    return (pulse_width_us * (wrap + 1)) / (1000000 / PWM_FREQUENCY);
}

void servo_rotate(uint16_t pulse_width_us) {
    pulse_width_us = (pulse_width_us < SERVO_MIN_US) ? SERVO_MIN_US : 
                     (pulse_width_us > SERVO_MAX_US) ? SERVO_MAX_US : 
                     pulse_width_us;
    
    pwm_set_gpio_level(SERVO_PIN, servo_calculate_pwm_level(pulse_width_us));
}

void servo_set_angle(float angle) {
    angle = (angle < 0) ? 0 : (angle > 180) ? 180 : angle;
    
    uint16_t pulse_width = SERVO_MIN_US + 
        (uint16_t)((angle / 180.0) * (SERVO_MAX_US - SERVO_MIN_US));
    
    servo_rotate(pulse_width);
}