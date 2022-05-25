#pragma once
//Pico MEMFS - The memory filesystem
//Stored in RAM. 100KB max. (very small but it works)
// - Dylan 2022 - PogOSM
#include <stdio.h>
#include "pico/stdlib.h" //For malloc() and free()
#include <string.h>
#include <stdlib.h>
char* fs;


int memfs_init(){
    //Reserve 100KB of memory for the filesystem
    fs = (char*) malloc(102400);
    if (fs == NULL) {
        return 1;
    }
    //Initialize the filesystem
    memset(fs, 0, 102400);
    return 0;
} 



uint32_t memfs_write(int ptr, char *data){
    for (int i = 0; i < strlen(data); i++) {
        fs[ptr + i] = data[i];
    }
    int next_ptr = ptr + strlen(data);
    return next_ptr;
}



char * memfs_read(int ptr, int len){
    char * data = (char*) malloc(len + 1);
    for (int i = 0; i < len; i++) {
        data[i] = fs[ptr + i];
    }
    data[len] = '\0';
    
    return data;
}


int memfs_delete(){
    free(fs);
    fs = NULL;
    return 0;
}

int memfs_print(char *data){
    for (int i = 0; i < strlen(data); i++) {
        putchar(data[i]);
    }
    return 0;
}


void memfs_delete_file(int ptr, int len){
    for (int i = 0; i < len; i++) {
        fs[ptr + i] = '\0';
    }
}