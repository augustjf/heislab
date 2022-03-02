#include "floor_module.h"

void floor_light_on() {
    int current_floor = elevio_floorSensor();
    if(current_floor != -1){
        elevio_floorIndicator(current_floor);
    }
    
}

void floor_button_light_on(){
    
    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_HALL_UP) == 1){
            elevio_buttonLamp(i, BUTTON_HALL_UP, 1);
        }
    }

    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_HALL_DOWN) == 1){
            elevio_buttonLamp(i, BUTTON_HALL_DOWN, 1);
        }
    }
    
    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_CAB) == 1){
            elevio_buttonLamp(i, BUTTON_CAB, 1);
        }
    }

}
