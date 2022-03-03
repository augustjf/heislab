#include "floor_module.h"


void floor_light_on() {
    int current_floor = elevio_floorSensor();
    if(current_floor != -1){
        elevio_floorIndicator(current_floor);
    }
    
}

void button_light_on(Order o){
    
    
    if( o.floor >= 0 && o.floor <= 3){
        elevio_buttonLamp(o.floor, o.btn, 1);    //because down-buttons are one level higher on board
    }
}


void button_light_off(Order o) {
    if(o.floor >= 0 && o.floor <= 3){
        elevio_buttonLamp(o.floor, o.btn, 0);    //because down-buttons are one level higher on board
    }

}