add_library(reboot
        reboot.c
)
add_library(fs  
        fs.c
)       
target_link_libraries(reboot pico_stdlib)
target_link_libraries(fs pico_stdlib)