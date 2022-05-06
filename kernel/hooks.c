#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include <stdarg.h>
#include "led.c"
#ifndef p_printf 
#define p_printf p_printf
int p_printf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    int ret = vprintf(format, args);
    va_end(args);
    //Extra Code Goes Here  
    //End Extra Code
    return ret;
}
#endif