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

int button_pin = 15;
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
        p_printf("set pin %d to %d\n", pin, state);
    }
    else if (is_eq(command_array[0], "set_multiple_pins")){
        //Check if there are enough arguments
        if (i < 4) {
            p_printf("Not enough arguments\n");
            return 1;
        }
        //Get start pin number 
        const uint pinStart = atoi(command_array[1]);
        //Get end pin number
        const uint pinEnd = atoi(command_array[2]);
        //Convert arg 1 to bool
        const bool state = atoi(command_array[3]);
        for (int current_pin = pinStart;current_pin-1 < pinEnd; current_pin++){
            gpio_init(current_pin);
            gpio_set_dir(current_pin, GPIO_OUT);
            gpio_put(current_pin, state);
            p_printf("set pin %d to %d\n",current_pin, state);    
        }        
    }
    
    else if (is_eq(command_array[0], "cls") || is_eq(command_array[0], "clear")) {
        p_printf("\e[1;1H\e[2J");
    }
    else if(is_eq(command_array[0], "calculate") || is_eq(command_array[0], "calc") || is_eq(command_array[0], "calculator") || is_eq(command_array[0], "cal")) {
        if(i < 4){
            p_printf("Not enough arguments\nUsage: calculate <number> <operator> <number>\n");
            return 1;
        }else{
            const int num1 = atoi(command_array[1]);
            const int num2 = atoi(command_array[3]);
            const char op = command_array[2][0];
            if(op == '+'){
                p_printf("%d + %d = %d\n", num1, num2, num1 + num2);}
            else if(op == '-'){
                p_printf("%d - %d = %d\n", num1, num2, num1 - num2);}
            else if(op == '*'){
                p_printf("%d * %d = %d\n", num1, num2, num1 * num2);}
            else if(op == '/' || op == ':' || op == '÷'){
                p_printf("%d / %d = %d\n", num1, num2, num1 / num2);}
            else if(op == '%'){
                p_printf("%d %% %d = %d\n", num1, num2, num1 % num2);}
            else{
                p_printf("Invalid operator\n");
                return 1;
            }
        }
    }
    else if (is_eq(command_array[0], "reboot")) {
        reboot();
    }
    else if (is_eq(command_array[0], "help")) {
        p_printf("https://github.com/poggingfish/pogosm\n");
    }
    
    else if (is_eq(command_array[0], "dbg") || is_eq(command_array[0], "debug")) {
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
    else if (is_eq(command_array[0], "button_enable")){
        //Enables the button
        p_printf("Starting catching button presses on pin 15\n");
        gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    gpio_pull_up(15);
    buttonEnabled = 1;
    }
    
    else if (is_eq(command_array[0], "disable_button")){
        //Disables the button
        if(buttonEnabled){
            p_printf("Stoping catching button presses on pin 15\n");
            buttonEnabled =0;
        }else{
            p_printf("Button is not enabled\n");
        }
        
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
        //Print input
        p_printf("Enter text: ");
        char *command_input = input();
        kern_write(command_input);
    }
    else if(is_eq(command_array[0], "led")){
        //Toogle LED
        toggle_led();
    }
    else if(is_eq(command_array[0], "reset_fs")){
        //Reset the filesystem
        memfs_delete();
        memfs_init();
        p_printf("Filesystem reset\n");
    }        
    else if(is_eq(command_array[0], "panic")){
        k_panic("This is a test panic");
    }
    else if (is_eq(command_array[0], "set_repeat_pin")){
        //Sets pin to repeat in loop
        led_to_blink = atoi(command_array[1]);
    }
    else if (is_eq(command_array[0], "disable_repeat_pin")){
        //Disables pin loop 
        gpio_put(led_to_blink,0);
        led_to_blink = 0;
    }
    else if (is_eq(command_array[0], "set_button_pin")){
        //Sets pin to button
        button_pin = atoi(command_array[1]);
    }    
    else if (is_eq(command_array[0], "credits") || is_eq(command_array[0], "credit")){
        //Print credits
        p_printf("PoggingFish ©2022 official\nMIT Licensed\n");
    }
    else if (is_eq(command_array[0], "author")){
        //Print author
        p_printf("PoggingFish pogging.fish\n");
    }
    else if (is_eq(command_array[0], "sleep")){
        sleep_ms(atoi(command_array[1]) * 1000);
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
