#include <stdio.h>
#include "pico/stdlib.h"
#include "../hooks.c"
#include "../led.c"
#include "../panic.c"
#ifndef core2_main
#define core2_main core2_main
void core2_main() {
    for (int i = 0; i < 100; i++) {
        toggle_led();
        sleep_ms(50);
    }
    while (1) {
        toggle_led();
        if(!gpio_get(15) && buttonEnabled){
            p_printf("Button pressed!\n");
        }
        sleep_ms(500);
    }
} 
#endif