add_library(before_boot
    before_boot.c
) 
add_library(core2
    core2.c
)
target_link_libraries(before_boot pico_stdlib)
target_link_libraries(core2 pico_stdlib )
target_link_libraries(core2 pico_multicore)