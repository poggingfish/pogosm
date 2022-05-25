#pragma once
#include <stdio.h>
#include "../hooks.c"
#include "pico/stdlib.h"
#include "hardware/watchdog.h"
#include "../syscall.c"
int reboot(){
    p_printf("Rebooting...\n");
    watchdog_enable(1, 1);
    while(1);
}