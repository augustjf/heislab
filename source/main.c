
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include "driver/elevio.h"
#include "floor_module.h"
#include "elev_module.h"
#include "queue_module.h"
#include "control_module.h"




int main(){

    
   


    elevio_init();
    
    printf("=== Example Program ===\n");
    printf("Press the stop button on the elevator panel to exit\n");
////////////////////////////////////////////////////////////////////////////
   
   enum ELEV_STATE state = INIT; 
   int prev_floor = -1;
   
   Order current_order;
   current_order.floor = -1;
   MotorDirection current_dirn;

    while(1){
        if(elevio_floorSensor() != -1){
            prev_floor = elevio_floorSensor();
        }
        
        //loops buttons to turn on
        stop();

    

        
      
        
        

        /*
        int floor = elevio_floorSensor();
        printf("floor: %d \n",floor);

        if(floor == 0){
            elevio_motorDirection(DIRN_UP);
        }

        if(floor == N_FLOORS-1){
            elevio_motorDirection(DIRN_DOWN);
        }


        for(int f = 0; f < N_FLOORS; f++){
            for(int b = 0; b < N_BUTTONS; b++){
                int btnPressed = elevio_callButton(f, b);
                elevio_buttonLamp(f, b, btnPressed);
            }
        }

        if(elevio_obstruction()){
            elevio_stopLamp(1);
        } else {
            elevio_stopLamp(0);
        }
        
        if(elevio_stopButton()){
            elevio_motorDirection(DIRN_STOP);
            break;
        }


        
        */
        nanosleep(&(struct timespec){0, 20*1000*1000}, NULL);
    }

    return 0;
}
