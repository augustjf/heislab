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


void go_to_floor(int floor, int *prev_floor, MotorDirection *dirn) {   

    if((floor - *prev_floor) > 0){
        elevio_motorDirection(DIRN_UP);
        dirn = DIRN_UP;
    }  

    else if((floor - *prev_floor) < 0) {
        elevio_motorDirection(DIRN_DOWN);
        dirn = DIRN_DOWN;
    }
    
    else if((floor - *prev_floor) == 0){
    //    elevio_motorDirection(DIRN_STOP);
        dirn = DIRN_STOP;
    }
}




void run_elevator(enum ELEV_STATE *state, MotorDirection *current_dirn, int *prev_floor){
    


    if(elevio_stopButton() == 1){  //må alltid sjekke om det er stop
        *state = STOP;
    }




    switch(*state){
        case INIT:
            for (int i = 0; i < 4; i++) {
                elevio_buttonLamp(i, BUTTON_CAB, 0);
            }
            for (int i = 0; i < 3; i++) {
                elevio_buttonLamp(i, BUTTON_HALL_UP, 0);
                elevio_buttonLamp(i+1, BUTTON_HALL_DOWN, 0);
            }

            empty_queue();
            elevio_stopLamp(0);
     
            if (elevio_floorSensor() == -1) {
                elevio_motorDirection(-1);
            }

            while (elevio_floorSensor() == -1){ //waits for elevator to reach a floor
            }

            elevio_motorDirection(0);
            *state = STANDBY;
            break;
        
        case STANDBY:
            //printf("standby");
            read_buttons(state, current_dirn, prev_floor);
            if(next_floor() != -1) {
                printf("next floor");
                printf("%d", next_floor());
                *state = GO_TO;
            }
            
           
            break;


        case STOP:
            printf("stop");
            empty_queue();
            elevio_motorDirection(0);

            if(elevio_floorSensor() != -1){
                door_handler(state, current_dirn, prev_floor);                       
            }

            while(elevio_stopButton() == 1) {
                elevio_stopLamp(1);
            }
            elevio_stopLamp(0);


            *state = STANDBY;
            break;

        case GO_TO:
            printf("!");
            printf("%d", current_dirn);
            printf("!");
            go_to_floor(next_floor(), prev_floor, current_dirn);
            floor_light_on();

            if(elevio_floorSensor() == next_floor()){
                *state = FLOOR_REACHED;
            }
            printf("goto");

            break;

        case FLOOR_REACHED:
            elevio_motorDirection(0);


            printf("floor reached");
            
    
            button_light_off(next_floor(), BUTTON_HALL_UP);
            button_light_off(next_floor(), BUTTON_HALL_DOWN);
            button_light_off(next_floor(), BUTTON_CAB);
            
            call_finished(next_floor());
            door_handler(state, current_dirn, prev_floor);
            
            
            *state = STANDBY;

            break;

        default:
            break;
    }
}




