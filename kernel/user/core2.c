#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "../hooks.c"
#include "../led.c"
#include "../panic.c"
#include "../shell.c"
int enable_button = 0;
bool led_rep_status = 0;
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
        if (led_to_blink != 0){
         gpio_init(led_to_blink);
        gpio_set_dir(led_to_blink, GPIO_OUT);
        gpio_put(led_to_blink, led_rep_status);
        led_rep_status = !led_rep_status;
        }
        
        sleep_ms(500);
    }
} 