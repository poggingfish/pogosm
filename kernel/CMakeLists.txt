add_subdirectory(utils)
add_subdirectory(user)
add_executable(kernel
        kernel.c
        )
add_library(hooks
        hooks.c
)
add_library(led
        led.c
)
add_library(shell
        shell.c
)
add_library(kernfs      
        kernfs.c
)
add_library(panic       
        panic.c
)

# pull in common dependencies
target_link_libraries(kernel pico_stdlib)
target_link_libraries(hooks pico_stdlib)
target_link_libraries(led pico_stdlib) 
target_link_libraries(shell pico_stdlib)
target_link_libraries(kernfs pico_stdlib)
target_link_libraries(panic pico_stdlib)
target_link_libraries(panic pico_multicore)
target_link_libraries(kernel pico_multicore)
pico_enable_stdio_usb(kernel 1)
pico_enable_stdio_uart(kernel 0)
pico_add_extra_outputs(kernel)