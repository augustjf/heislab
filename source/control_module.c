#include "control_module.h"





void init_floor(void){
        if (elevio_floorSensor() == -1) {
            elevio_motorDirection(-1);
        }

    while (elevio_floorSensor() == -1){ //waits for elevator to reach a floor
    }

    elevio_motorDirection(0);
}

void stop(MotorDirection *dirn){
    int stop_yn = elevio_stopButton();
    if(stop_yn == 1){
        elevio_stopLamp(1);
        elevio_motorDirection(0);
        *dirn = DIRN_STOP;
    } 
    else{
        elevio_stopLamp(0);
    }
}


int go_to_floor(int floor, int *prev_floor, MotorDirection *dirn){
            

    if((floor - *prev_floor) > 0 ){
        elevio_motorDirection(DIRN_UP);
        dirn = DIRN_UP;
    }

    

    else if((floor - *prev_floor) < 0) {
        elevio_motorDirection(DIRN_DOWN);
        dirn = DIRN_DOWN;
    }

    
    else if((floor - *prev_floor) == 0){
        elevio_motorDirection(DIRN_STOP);
        dirn = DIRN_STOP;
        return 1;
    }
}




void run_elevator(enum ELEV_STATE *state, MotorDirection *current_dirn, int *prev_floor){
    


    if(elevio_stopButton() == 1){  //må alltid sjekke om det er stop
        state = STOP;
    }


    enum ELEV_STATE deref_state = *state;

    switch(deref_state){
        case INIT:
            if (elevio_floorSensor() == -1) {
                elevio_motorDirection(-1);
            }

            while (elevio_floorSensor() == -1){ //waits for elevator to reach a floor
            }

            elevio_motorDirection(0);
            *state = STANDBY;
            break;
        
        case STANDBY:
            if(next_floor() != -1) {
                *state = GO_TO;
            }
            
            
            *state = STANDBY;
            break;

        case STOP:
            elevio_motorDirection(0);

            if(elevio_floorSensor() != -1){
                    floor_reached();
                                            
                }

            while(elevio_stopButton() == 1) {
                elevio_stopLamp(1);
                //delete queue
                
            }
            
            init_floor();
            *state = STANDBY;
            break;

        case GO_TO:
            read_buttons(state, current_dirn, prev_floor);
            go_to_floor(next_floor(), prev_floor, current_dirn);
            break;

        case FLOOR_REACHED:
            //stop
            //floor_reached
            //empty_queue
            break;

        default:
            break;
    }
}




