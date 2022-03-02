#include "queue_module.h"

//Make function to increase array size if needed
int on_the_way_orders[3]; //orders coming from a floor as the cab is moving in that direction
int cab_orders[50]; //orders from the cab, initialized to 50
int floor_orders[50]; //orders form the floors

void add_to(int arr[], int call) {
    for (int i = 0; i < sizeof(arr); i++) {
        if (arr[i] == 0) {
            arr[i] = call;
            break;
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
}

void add_call(ELEV_STATE state, MotorDirection dirn, int prev_floor, int call_floor, ButtonType btn) {
    //PRIORITIZER//

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
