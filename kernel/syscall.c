// PogOS Syscall Library

#include <pico/stdlib.h>
#include "hooks.c"
#include <stdarg.h>
int syscall(int call, ...) {
    int write = 0; // Gets what to write from the syscall
    va_list args;
    if (call == write) {
        // Get the integer to print from the first argument
        int arg = va_arg(args, int);
        // Print the integer
        p_printf("%d", arg);
    }
}