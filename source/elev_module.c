#include "elev_module.h"

void floor_reached() {
    elevio_doorOpenLamp(1);

    int sec = 0;
    int trigger = 3;
    clock_t clock_init = clock();

    while(sec < trigger) {
        if(elevio_obstruction()) {
            clock_init = clock();
        }
        if(elevio_stopButton()){
            break;
        }
        clock_t differense = clock() - clock_init;
        sec = differense / CLOCKS_PER_SEC;
    }
    
    if(elevio_stopButton()){
        check_stop();
    }
    else{
        elevio_doorOpenLamp(0);
    }
}