#include <stdio.h>
#include "pico/stdlib.h"
#include "pico/multicore.h"
#include "hooks.c"
#include "led.c"
#include "shell.c"
#include "user/core2.c"
#include "user/before_boot.c"
#include "utils/fs.c"
#include "kernfs.c"
uint8_t major = 0;
uint8_t minor = 4;
int main() {
    
    while (stdio_usb_connected == false) {
        //Wait for USB to be connected
        sleep_ms(50);
    }
    multicore_launch_core1(core2_main);
    before_boot();
    toggle_led();
    stdio_init_all();
    p_printf("PogOS Initializing...\n");
    sleep_ms(2500);
    p_printf("MemFS initializing...\n");
    memfs_init();
    p_printf("MemFS initialized\n");
    p_printf("Creating a test file...\n");
    kern_write("Hello World!\n");
    p_printf("Test file created\n");
    //Read the files contents
    p_printf("File contents: ");
    p_printf(kern_read(0));
    p_printf("\n");
    memfs_delete();
    kernfs_delete_delete();
    memfs_init();
    p_printf("All files start at ptr 1\n");
    p_printf("File 0 is blank\n");
    char * test = kern_read(0);
    memfs_print(test);
    printf("\n");
    printf("\n");
    p_printf("|‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾|\n");
    p_printf("|          PogOS is ready!          |\n");
    p_printf("|    Everything is working fine.    |\n");
    p_printf("|___________________________________|\n");
    p_printf("PogOS v%d.%d\n", major, minor);
    //Start shell
    toggle_led();
    shell_init();
    return 0;
}
