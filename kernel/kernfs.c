//Kernel Tools For Filesystems 

#include <stdio.h>
#include "pico/stdlib.h"
#include "string.h"  
#include "utils/fs.c"
#include <string.h>
#ifndef ptr
#define ptr ptr
uint32_t ptr = 0;
#endif
#ifndef ptrs
#define ptrs ptrs
uint32_t ptrs[4096];
#endif
#ifndef lens
#define lens lens
uint32_t lens[4096];
#endif
#ifndef ptriter
#define ptriter ptriter
int ptriter = 0;
#endif
#ifndef next_ptr
#define next_ptr next_ptr
int next_ptr = 0;
#endif
#ifndef last_ptr
#define last_ptr last_ptr  
int last_ptr = 0; 
#endif
#ifndef kern_write
#define kern_write kern_write
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
#endif
#ifndef kern_read
#define kern_read kern_read
char * kern_read(int ptr){
    char * read = memfs_read(ptrs[ptr], lens[ptr]);
    return read;
}
#endif