//Pico MEMFS - The memory filesystem
//Stored in RAM. 100KB max. (very small but it works)
// - Dylan 2022 - PogOS for microcontrollers
#include <stdio.h>
#include "pico/stdlib.h" //For malloc() and free()
#include <string.h>
#include <stdlib.h>
char* fs;

#ifndef memfs_init
#define memfs_init memfs_init
int memfs_init(){
    //Reserve 100KB of memory for the filesystem
    fs = (char*) malloc(102400);
    //Make FS a global variable
    if (fs == NULL) {
        return -1;
    }
    //Initialize the filesystem
    return 0;
} 
#endif

#ifndef memfs_write
#define memfs_write memfs_write
int memfs_write(int ptr, char *data){
    for (int i = 0; i < strlen(data); i++) {
        fs[ptr + i] = data[i];
    }
    uint8_t next_ptr = ptr + strlen(data);
    return next_ptr;
}
#endif

#ifndef memfs_read
#define memfs_read memfs_read
char * memfs_read(int ptr, int len){
    char * data = (char*) malloc(len + 1);
    for (int i = 0; i < len; i++) {
        data[i] = fs[ptr + i];
    }
    data[len] = '\0';
    return data;
}
#endif

#ifndef memfs_delete 
#define memfs_delete memfs_delete
int memfs_delete(){
    free(fs);
    return 0;
}
#endif

#ifndef memfs_print
#define memfs_print memfs_print
int memfs_print(char *data){
    for (int i = 0; i < strlen(data); i++) {
        putchar(data[i]);
    }
    return 0;
}
#endif