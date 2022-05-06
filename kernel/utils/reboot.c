#include <stdio.h>
#include "pico/stdlib.h"
#ifndef reboot
#define reboot reboot
int reboot(){
    p_printf("Rebooting...\n");
    watchdog_enable(1, 1);
    while(1);
}
#endif