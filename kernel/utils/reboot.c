#include <stdio.h>
#include "pico/stdlib.h"
int reboot(){
    p_printf("Rebooting...\n");
    watchdog_enable(1, 1);
    while(1);
}