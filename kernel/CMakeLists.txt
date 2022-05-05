add_executable(kernel
        kernel.c
        )

# pull in common dependencies
target_link_libraries(kernel pico_stdlib)
pico_enable_stdio_usb(kernel 1)
pico_enable_stdio_uart(kernel 0)
pico_add_extra_outputs(kernel)