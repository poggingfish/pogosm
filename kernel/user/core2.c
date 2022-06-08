#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "../hooks.c"
#include "../led.c"
#include "../panic.c"
#include "../shell.c"
int enable_button = 0;
void core2_main() {
    for (int i = 0; i < 100; i++) {
        toggle_led();
        sleep_ms(50);
    }
    while (1) {
        buttonPressed = 0;
        toggle_led();
        if (enable_button) {
            if(!gpio_get(15) && buttonEnabled){
                buttonPressed = 1;
            }
        }
        sleep_ms(500);
    }
} 