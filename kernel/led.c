#include "pico/stdlib.h"
#pragma once
bool LED_state = false;
void toggle_led() {
    LED_state = !LED_state;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, LED_state);
} 