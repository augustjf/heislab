#include "elev_module.h"

void open_door(){
    elevio_doorOpenLamp(1);
}

void close_door() {
    int obstruction_yn = elevio_obstruction();
    if(obstruction_yn != 0){
        //start timer
    }
}