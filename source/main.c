
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "floor_module.h"
#include "elev_module.h"
#include "control_module.h"




int main(){

    
   


    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
////////////////////////////////////////////////////////////////////////////
   
    enum ELEV_STATE state = INIT; 
    enum ELEV_STATE *state_ptr;
    state_ptr = &state;

    int prev_floor = -1;
    int *prev_floor_ptr;
    prev_floor_ptr = &prev_floor;
   

    MotorDirection current_dirn = STOP;
    MotorDirection *current_dirn_ptr;
    current_dirn_ptr = current_dirn;

    empty_queue();


    while(1){
        read_buttons(state_ptr, current_dirn_ptr, prev_floor_ptr);
        if(elevio_floorSensor() != -1){
            *prev_floor_ptr = elevio_floorSensor();
        }
        run_elevator(state_ptr, current_dirn_ptr, prev_floor_ptr);

        


    

        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
