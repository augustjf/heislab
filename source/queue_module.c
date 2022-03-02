#include "queue_module.h"

//Make function to increase array size if needed
int on_the_way_orders[50] = {0}; //orders coming from a floor as the cab is moving in that direction
int cab_orders[50] = {0}; //orders from the cab, initialized to 50
int floor_orders[50] = {0}; //orders form the floors

void add_to(int arr[], int call) {
    for (int i = 0; i < 50; i++) {
        if (arr[i] == 0) {
            arr[i] = call;
            break;
        }
    }
}

void call_finished(int current_floor) {
    if (on_the_way_orders[0] == current_floor) {
        for (int i = 0; i < (50 - 1); i++) {
            on_the_way_orders[i] = on_the_way_orders[i+1];
        }
    }    
    else if (cab_orders[0] == current_floor) {
        for (int i = 0; 1 < (50 - 1); i++) {
            cab_orders[i] = cab_orders[i+1];
        }
    }
    else if (floor_orders[0] == current_floor) {
        for (int i = 0; 1 < (50 - 1); i++) {
            floor_orders[i] = floor_orders[i+1];
        }
    }
}

int next_floor() {

    if (on_the_way_orders[0] != 0) {
        return on_the_way_orders[0];
    }
    else if (cab_orders[0] != 0 && on_the_way_orders[0] == 0) {
        return cab_orders[0];
    }
    else if (floor_orders[0] != 0 && cab_orders[0] == 0 && on_the_way_orders[0] == 0) {
        return floor_orders[0];
    }

    return -1;
}



void add_call(ELEV_STATE state, MotorDirection dirn, int call_floor, int prev_floor, ButtonType btn) {
    //PRIORITIZER//
    int already_in_queue = 0;
    for (int i = 0; i < 50; i++) {
        if(on_the_way_orders[i] == call_floor || cab_orders[i] == call_floor || floor_orders[i] == call_floor) {
            already_in_queue = 1;
            break;
        }
    }

    if(already_in_queue = 0) {
        if (state == STANDBY) {
            if (btn == BUTTON_CAB) {
                add_to(cab_orders, call_floor);
            }
            else if (btn == BUTTON_HALL_DOWN || btn == BUTTON_HALL_UP) {
                add_to(floor_orders, call_floor);
            }

            //on_the_way_orders cannot happen in STANDBY
        }

        if (state == GO_TO) {
            if (btn == BUTTON_CAB) {
                add_to(cab_orders, call_floor);
            }
            else if (btn == BUTTON_HALL_DOWN) {
                if (dirn == DIRN_DOWN && call_floor < prev_floor) {
                    add_to(on_the_way_orders, call_floor);
                }
                else {
                    add_to(floor_orders, call_floor);
                }

            }
            else if (btn == BUTTON_HALL_UP) {
                if (dirn == DIRN_UP && call_floor > prev_floor) {
                    add_to(on_the_way_orders, call_floor);
                }
                else {
                    add_to(floor_orders, call_floor);
                }
            }
        }
    }
}
