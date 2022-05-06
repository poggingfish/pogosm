#include "pico/stdlib.h"
#ifndef LED_state
#define LED_state LED_state
bool LED_state = false;
#endif
#ifndef toggle_led
#define toggle_led toggle_led
void toggle_led() {
    LED_state = !LED_state;
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN, LED_state);
} 
#endif