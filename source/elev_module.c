#pragma once
#include "elev_module.h"

void close_door() {
    int sec = 0;
    int trigger = 3;
    clock_t clock_init = clock();

    while(sec < trigger) {
        if(elevio_obstruction()) {
            clock_t clock_init = clock();
        }
        clock_t differense = clock() - clock_init;
        sec = differense / CLOCKS_PER_SEC;
    }
    
    elevio_doorOpenLamp(0);
}