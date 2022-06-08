#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "hooks.c"
#include "utils/reboot.c"
#include "utils/fs.c"
#include "kernfs.c"
#include "stdin.c"
#include "pcolor.c"
#include "panic.c"

int led_to_blink = 0;
int buttonEnabled = 0;
int buttonPressed = 0;
int BACKSPACE_CHAR = 127;
int is_eq(char *a, char *b) {
    return strcmp(a, b) == 0;
}
bool shell_dbg = false;
int parse_command(char shell_buffer[]) {
    char *command_array[512];
    int i = 0;
    char *token = strtok(shell_buffer, " ");
    while (token != NULL) {
        command_array[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    command_array[i] = NULL;
    if (is_eq(command_array[0], "set_pin")){
        //Check if there are enough arguments
        if (i < 3) {
            p_printf("Not enough arguments\n");
            return 1;
        }
        const uint pin = atoi(command_array[1]);
        //Convert arg 1 to bool
        const bool state = atoi(command_array[2]);
        gpio_init(pin);
        gpio_set_dir(pin, GPIO_OUT);
        gpio_put(pin, state);
        p_printf("set pin to %d\n", state);
    }
    else if (is_eq(command_array[0], "cls") || is_eq(command_array[0], "clear")) {
        p_printf("\e[1;1H\e[2J");
    }
    else if (is_eq(command_array[0], "reboot")) {
        reboot();
    }
    else if (is_eq(command_array[0], "dbg")) {
        shell_dbg = !shell_dbg;
        p_printf("Debug mode: %s\n", shell_dbg ? "on" : "off");
    }
    else if (is_eq(command_array[0], "rm") || is_eq(command_array[0], "del") || is_eq(command_array[0], "delete" )){
        if (i < 1) {
            p_printf("Not enough arguments\n");
            return 1;
        }
        kern_delete((int)command_array[1]);
    }
    else if (is_eq(command_array[0], "button")){
        p_printf("Starting catching button presses on pin 15\n");
        gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    gpio_pull_up(15);
    buttonEnabled = 1;
    }

    else if(is_eq(command_array[0], "read")) {
        memfs_print(kern_read(atoi(command_array[1])));
    }
    else if (is_eq(command_array[0], "ls")) {
        //Get the files in the filesystem
        for (int i = 0; i < ptriter; i++) {
            p_printf("%d: %s\n", i, kern_read(i));
        }
    }
    else if (is_eq(command_array[0], "write") || is_eq(command_array[0], "echo")) {
        //Get input
        p_printf("Enter text: ");
        char *command_input = input();
        kern_write(command_input);
    }
    else if(is_eq(command_array[0], "led"))
    {
        toggle_led();
        //made by stigl, fixed by poggingfish C2022
    }
    else if(is_eq(command_array[0], "reset_fs")){
        memfs_delete();
        memfs_init();
        printf("Filesystem reset\n");
    }        
    else if(is_eq(command_array[0], "panic")){
        k_panic("This is a test panic");
    }
    else if (is_eq(command_array[0], "set_repeat_pin")){
        led_to_blink = atoi(command_array[1]);
    }    
    else if (is_eq(command_array[0], "credits") || is_eq(command_array[0], "credit")){
        printf("PoggingFish ©2022 official not moded version\nMIT Licensed\n");
    }
    else if (is_eq(command_array[0], "")){
    }
    
    
    else{
        p_printf("Unknown command %s\n", command_array[0]);
    }
}
int shell_init() {
    p_printf(cyan);
    p_printf(bold);
    p_printf("$~ ");
    p_printf(white);
    while (1){
        char * command_input = input();
        printf(reset);
        parse_command(command_input);
        p_printf(cyan);
        p_printf(bold);
        p_printf("$~ ");
        p_printf(white);
    }
}
