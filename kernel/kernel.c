#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h" 
uint8_t major = 0;
uint8_t minor = 1;
int parse_command(char shell_buffer[]) {
    //If the command is equal to "version" then print the version number
    if (strcmp(shell_buffer, "version") == 0) {
        printf("Version: 1.0\n");
        return 0;
    }
}
int shell_init() {
    char shell_buffer[256];
    int i = 0;
    printf("$ ");
    while (true){
    //Check if the shell buffer has overflowed
    if (i == 256) {
        printf("\nShell buffer overflow!\n");
        for (int j = 0; j < 256; j++) {
            shell_buffer[j] = '\0';
            i = 0;
        }
    }
    //Get one character at a time
    shell_buffer[i] = getchar();
    putchar(shell_buffer[i]);
    i++;
    //Check if the input is a carriage return
    if (shell_buffer[i-1] == '\r') {
        shell_buffer[i-1] = '\0';
        i = 0;
        parse_command(shell_buffer);
        for (int j = 0; j < 256; j++){
            shell_buffer[j] = '\0';
        }
        printf("$ ");
    }
}}
int main() {

    stdio_init_all();
    printf("PogOS Initializing...\n");
    sleep_ms(1000);
    printf("PogOS v%d.%d\n", major, minor);
    printf("PogOS is ready!\n");
    //Start shell
    shell_init();
    return 0;
}
