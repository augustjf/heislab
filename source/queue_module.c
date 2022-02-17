
#include "queue_module.h"

void stop(){
    int stop_yn = elevio_stopButton();
    if(stop_yn == 1){
        elevio_stopLamp(1);
    } 
}