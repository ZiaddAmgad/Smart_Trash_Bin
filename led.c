#include "led.h"

void led_init() {
    gpio_init(GREEN_LED_PIN);
    gpio_set_dir(GREEN_LED_PIN, GPIO_OUT);
    gpio_init(RED_LED_PIN);
    gpio_set_dir(RED_LED_PIN, GPIO_OUT);
}

void led_red_toggle(bool state) {
    gpio_put(RED_LED_PIN, state);
}

void led_green_toggle(bool state) {
    gpio_put(GREEN_LED_PIN, state);
}