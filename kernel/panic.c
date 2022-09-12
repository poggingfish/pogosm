#include <stdio.h>
#include "pico/stdlib.h"
#include "utils/reboot.c"
#include "pico/multicore.h"
#include <string.h>
#pragma once
void k_panic(const char *msg) {
    p_printf("\n");
    for (int x = 0; x < strlen(msg)+strlen("Panic:\n"); x++) {
        putchar('!');
    }
    p_printf("\n");
    p_printf("Panic: %s\n", msg);
    if (get_core_num() == 1) {
    p_printf("Panics called from core 2 are not supported.\n");
    reboot();
    }
    p_printf("Press R to reboot\n");

    p_printf("Press D to dump memory\n");
    p_printf("Press S to dump memory and then reboot\n");
    while (1){
        char c = getchar();
        if (c == 'r'){
            reboot();
        }
        if (c == 'd'){
            //Pi Pico has 264KB of memory
            //Print: hex address : hex data
            for (int x = 0; x < 264*1024; x++) {
                printf("%x : %x\n", x, *(uint8_t*)x);
            };
        }
        if (c == 's'){
            //Pi Pico has 264KB of memory
            //Print: hex address : hex data
            for (int x = 0; x < 264*1024; x++) {
                printf("%x : %x\n", x, *(uint8_t*)x);
            };
            reboot();
        }
    }
}