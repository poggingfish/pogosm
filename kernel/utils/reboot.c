#include <stdio.h>
#include "../hooks.c"
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#ifndef reboot
#define reboot reboot
int reboot(){
    p_printf("Rebooting...\n");
    watchdog_enable(1, 1);
    while(1);
}
#endif