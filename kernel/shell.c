#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"
#include "hooks.c"
#include "utils/reboot.c"
int BACKSPACE_CHAR = 127;
#ifndef is_eq
#define is_eq is_eq
int is_eq(char *a, char *b) {
    return strcmp(a, b) == 0;
}
#endif

#ifndef shell_dbg
#define shell_dbg shell_dbg
bool shell_dbg = false;
#endif

#ifndef parse_command
#define parse_command parse_command
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
    else if (is_eq(command_array[0], "")){
    }
    else{
        p_printf("Unknown command %s\n", command_array[0]);
    }
}
#endif

#ifndef shell_init
#define shell_init shell_init
int shell_init() {
    char shell_buffer[256];
    char character;
    int ascii;
    bool bad_key = false;
    int i = 0;
    p_printf("$ ");
    while (true){
    bad_key = false;
    //Check if the shell buffer has overflowed
    if (i == 256) {
        p_printf("\nShell buffer overflow!\n");
        for (int j = 0; j < 256; j++) {
            shell_buffer[j] = '\0';
            i = 0;
        }
    }
    //Get one character at a time
    character = getchar();
    if(shell_dbg){
        //print the character as an integer
        p_printf("%d\n", character);
    }
    //Check if character is the arrow keys

    //Turn character into an int
    ascii = character;
    if (bad_key == false) {
        shell_buffer[i] = character;
        putchar(shell_buffer[i]);
        i++;
        //Check if the input is a carriage return
        if (shell_buffer[i-1] == '\r') {
            shell_buffer[i-1] = '\0';
            i = 0;
            p_printf("\n");
            parse_command(shell_buffer);
            for (int j = 0; j < 256; j++){
                shell_buffer[j] = '\0';
            }
            p_printf("$ ");
        }
        if (ascii == BACKSPACE_CHAR) {
            if (i-1 < 1) {
                i--;
                p_printf("%c", ascii);
                continue;
            }
            shell_buffer[i-1] = '\0';
            i--;
            i--;
            p_printf("\b \b");
        }
    }
}
}
#endif
