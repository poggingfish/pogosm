#include <stdio.h>
#include <pico/stdlib.h>

#ifndef shell_buffer
#define shell_buffer shell_buffer 
char shell_buffer[256];
#endif
// ### Stdin library
char * input(){
    for (int i = 0; i < 256; i++) {
        shell_buffer[i] = 0;
    }
    char character;
    int ascii;
    int i = 0;
    int  BACKSPACE_CHAR = 127;
    bool finished = false;
    while (finished == false) {
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
    //Check if character is the arrow keys

    //Turn character into an int
    ascii = character;
    shell_buffer[i] = character;
    putchar(shell_buffer[i]); 
    i++;
    //Check if the input is a carriage return
    if (shell_buffer[i-1] == '\r') {
        shell_buffer[i-1] = '\0';
        i = 0;
        p_printf("\n");
        finished = true;
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
    return shell_buffer; 
}