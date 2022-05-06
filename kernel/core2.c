#include <stdio.h>
#include "pico/stdlib.h"
#include "hooks.c"
#include "led.c"

#ifndef core2_main
#define core2_main core2_main
void core2_main() {
    while (1) {
        toggle_led();
        sleep_ms(500);
    }
} 
#endif