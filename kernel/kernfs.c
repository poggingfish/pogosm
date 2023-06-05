//Kernel Tools For Filesystems 
#pragma once
#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"  
#include "utils/fs.c"
#include <string.h>
uint32_t ptr = 0;
uint32_t ptrs[4096];
uint32_t lens[4096];
int ptriter = 0;
int next_ptr = 0;
int last_ptr = 0; 
int kern_write(char *data){
    next_ptr = memfs_write(ptr, data);
    //Print ptr
    last_ptr = ptr;
    ptrs[ptriter] = last_ptr;
    ptr = next_ptr;
    lens[ptriter] = strlen(data);
    ptriter++;
    return 0;
}
char * kern_read(int ptr){
    char * read = memfs_read(ptrs[ptr], lens[ptr]);
    return read;
}
int kern_delete(int ptr){
    memfs_delete_file(ptrs[ptr], lens[ptr]);
    //Get rid of the pointer in the arrays
    for (int i = ptr; i < ptriter; i++) {
        ptrs[i] = ptrs[i + 1];
        lens[i] = lens[i + 1];
    }   
    ptr -= lens[ptriter];
    ptriter--;
    return 0;
}
int kernfs_delete_delete(){
    ptr = 0;
    next_ptr = 0;
    last_ptr = 0;
    ptriter = 0;
}