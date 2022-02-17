#pragma once
#include "elev_module.h"

void close_door() {
    int obstruction_yn = elevio_obstruction();
    if(obstruction_yn != 0){
        //start timer
    }
}