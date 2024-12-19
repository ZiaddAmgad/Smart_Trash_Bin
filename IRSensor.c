#include "IRSensor.h"

void ir_sensor_init() {
    gpio_init(IR_SENSOR_PIN);
    gpio_set_dir(IR_SENSOR_PIN, GPIO_IN);
    
    gpio_init(ONBOARD_LED_PIN);
    gpio_set_dir(ONBOARD_LED_PIN, GPIO_OUT);
    
    gpio_init(USER_LED_PIN);
    gpio_set_dir(USER_LED_PIN, GPIO_OUT);
}

bool ir_object_detected() {
    return !gpio_get(IR_SENSOR_PIN);
}