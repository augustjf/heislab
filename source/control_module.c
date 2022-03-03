#include "control_module.h"

#include "queue_module.h"


void init_floor(void){
        if (elevio_floorSensor() == -1) {
            elevio_motorDirection(-1);
        }

    while (elevio_floorSensor() == -1){ //waits for elevator to reach a floor
    }

    elevio_motorDirection(0);
}

void stop(){
    int stop_yn = elevio_stopButton();
    if(stop_yn == 1){
        elevio_stopLamp(1);
        elevio_motorDirection(0);
    } 
    else{
        elevio_stopLamp(0);
    }
}


void go_to_floor(int floor, int prev_floor){
            

    if(elevio_floorSensor() != -1){
        prev_floor = elevio_floorSensor();
    }
    
    
    if((floor - prev_floor) > 0 ){
        elevio_motorDirection(DIRN_UP);
    }

    

    else if((floor - prev_floor) < 0) {
        elevio_motorDirection(DIRN_DOWN);
    }

    
    else if((floor - prev_floor) == 0){
        elevio_motorDirection(DIRN_STOP);
        
    }
}


void run_elevator(ELEV_STATE state, MotorDirection current_dirn, int prev_floor){
        
    if(elevio_stopButton() == 1){  //må alltid sjekke om det er stop
        state = STOP;
    }

    switch(state){
        case INIT:
            if (elevio_floorSensor() == -1) {
                elevio_motorDirection(-1);
            }

            while (elevio_floorSensor() == -1){ //waits for elevator to reach a floor
            }

            elevio_motorDirection(0);
            state = STANDBY;
            break;
        
        case STANDBY:
            //while not order, wait
            //add_order(standby, dirn, )
            //if order, state = GO_TO

            Order current_order = read_buttons();
            add_call(STANDBY, current_dirn, prev_floor, current_order.floor, current_order.btn);
            
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
            state = STANDBY;
            break;

        case GO_TO:
            

            break;

        case FLOOR_REACHED:
            
            break;

        default:
            break;
    }
}


Order read_buttons() {
    Order current_order;
    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_HALL_UP) == 1){
            current_order.floor = i;                    //+1 because down buttons are one level higher on board
            current_order.btn = BUTTON_HALL_UP;

        }
        if(elevio_callButton(i, BUTTON_HALL_DOWN) == 1){
            current_order.floor = i;
            current_order.btn = BUTTON_HALL_DOWN;
        }
    }

    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_CAB) == 1){
            current_order.floor = i;
            current_order.btn = BUTTON_CAB;
        }

    }
    return current_order;
}

