#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h" 
uint8_t major = 0;
uint8_t minor = 1;
int BACKSPACE_CHAR = 127;
int is_eq(char *a, char *b) {
    return strcmp(a, b) == 0;
}
int cls(){
    printf("\033[2J\033[H");
}
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
    

}
int shell_init() {
    char shell_buffer[256];
    char character;
    int ascii;
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
    character = getchar();
    //Turn character into an int
    ascii = character;
    shell_buffer[i] = character;
    putchar(shell_buffer[i]);
    i++;
    //Check if the input is a carriage return
    if (shell_buffer[i-1] == '\r') {
        shell_buffer[i-1] = '\0';
        i = 0;
        printf("\n");
        parse_command(shell_buffer);
        for (int j = 0; j < 256; j++){
            shell_buffer[j] = '\0';
        }
        printf("$ ");
    }
    if (ascii == BACKSPACE_CHAR) {
        if (i-1 < 1) {
            i--;
            printf("%c", ascii);
            continue;
        }
        shell_buffer[i-1] = '\0';
        i--;
        i--;
        printf("\b \b");
    }
}}
int main() {

    stdio_init_all();
    printf("PogOS Initializing...\n");
    sleep_ms(1000);
    printf("PogOS v%d.%d\n", major, minor);
    printf("PogOS is ready!\n");
    //Clear the screen
    cls();
    //Start shell
    shell_init();
    return 0;
}
