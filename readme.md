# PogOS Micro
### Written in C
### An extremely lightweight OS for Raspberry Pi Pico



# Adding features

#### Always replace printf with p_printf 
#### This is because PogOS hooks to p_printf. printf and p_printf have the exact same functionality. 

# Commands
#### set_pin - Set the pin state. Usage: set_pin pinNumber 0/1
#### cls/clear - Clear the console.
#### reboot - Reboot raspberry pi pico.
#### dbg - toggle debug mode.
#### rm/del/delete - Delete the file in filesystem. Usage: del fileIndex.
#### read - Read the file. Usage: read fileIndex.
#### write/echo - Write the new file. 
#### ls - Show all content of filesystem.
#### reset_fs - Reset filesystem.
#### panic - Start the panic mode.
#### set_multiple_pins - Set multiple pins. Usage: set_multiple_pins fromPin toPin state