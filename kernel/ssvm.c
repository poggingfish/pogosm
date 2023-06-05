#include <stdio.h>
#include "pico/stdlib.h"
#include "hooks.c"
#include "utils/reboot.c"
int bytes[512];
int reg[256];
int executionDisabled = 0;
int execute_ssvm_code(){
    for(int i =0; i < 512;i++){
        if(executionDisabled){
            if(bytes[i] == 16)
                executionDisabled = 0;
            continue;
        }
        switch(bytes[i]){
            case 1:
                reg[bytes[++i]] = reg[bytes[++i]];
                break;
            case 2:
                int val = bytes[++i];
                reg[bytes[++i]] = val;
                break;
            case 3:
                reboot();
                break;
            case 4:
                int lenght = bytes[0];
                for(int j =1; j < lenght && j < 255;j++){
                    p_printf(bytes[j]);
                }break;
            case 5:
                //TODO: Inputs!
                break;
            case 6:
                reg[bytes[++i]] += reg[bytes[++i]];
                break;
            case 7:
                reg[bytes[++i]] -= reg[bytes[++i]];
                break;
            case 8:
                reg[bytes[++i]] *= reg[bytes[++i]];
                break;
            case 9:
                reg[bytes[++i]] /= reg[bytes[++i]];
                break;
            case 10:
                i = bytes[++i] - 1;
                break;
            case 11:
                int src = reg[bytes[++i]];
                if(reg[1] == src)
                    reg[0] = 0;
                else if(reg[1] == 0)
                    reg[0] = 2;
                else if(reg[1] > src)
                    reg[0] = 1;
                else if(reg[1] < src)
                    reg[0] = -1;
                else reg[0] = -2;
                break;
            case 12:
                if(reg[0] == 0)
                    i = bytes[++i] - 1;
                break;
            case 13:
                if(reg[0] != 0)
                    i = bytes[++i] - 1;
                break;
            case 14:
                if(reg[0] != 2)
                    i = bytes[++i] - 1;
                break;
            case 15:
                executionDisabled = 1;
                break;
            case 17:
                i = reg[0] -1;
                break;
            //Stacks not added!
        }
    }
}