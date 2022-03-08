#include "queue_module.h"

// Make function to increase array size if needed
int on_the_way_orders[20]; // orders coming from a floor as the cab is moving in that direction
int cab_orders[20];        // orders from the cab, initialized to 50
int floor_orders[20];      // orders form the floors
int array_size = 20;

void empty_queue() {
    for (int i = 0; i < array_size; i++) {
        on_the_way_orders[i] = -1;
        cab_orders[i] = -1;
        floor_orders[i] = -1;
    }
}

void add_to(int arr[], int call) {
    for (int i = 0; i < array_size; i++) {
        if (arr[i] == -1) {
            arr[i] = call;
            break;
        }
    }
    print_arrays();
}

void call_finished(int current_floor) {
    if (on_the_way_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            on_the_way_orders[i] = on_the_way_orders[i + 1];
        }
    }
    else if (cab_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            cab_orders[i] = cab_orders[i + 1];
        }
    }
    else if (floor_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            floor_orders[i] = floor_orders[i + 1];
        }
    }
    printf("call finished");
}

int next_floor() {
    if (on_the_way_orders[0] != -1) {
        return on_the_way_orders[0];// on_the_way_orders cannot happen in STANDBY
    }
    if((cab_orders[0] != 1) && (on_the_way_orders[0] == -1)) {
        return cab_orders[0];
    }
    if ((floor_orders[0] != -1) && (cab_orders[0] == -1) && (on_the_way_orders[0] == -1)) {
        return floor_orders[0];
    }
    else {
        return -1;
    }
}

void read_buttons(enum ELEV_STATE *state, MotorDirection *dirn, int *prev_floor) {
    for (int i = 0; i < 4; i++) {
        if (elevio_callButton(i, BUTTON_HALL_UP) == 1) {
            add_call(state, dirn, i, prev_floor, BUTTON_HALL_UP);
            button_light_on(i, BUTTON_HALL_UP);
        }
        else if (elevio_callButton(i, BUTTON_HALL_DOWN) == 1) {
            add_call(state, dirn, i, prev_floor, BUTTON_HALL_DOWN);
            button_light_on(i, BUTTON_HALL_DOWN);
        }
        else if (elevio_callButton(i, BUTTON_CAB) == 1) {
            add_call(state, dirn, i, prev_floor, BUTTON_CAB);
            button_light_on(i, BUTTON_CAB);
            printf(" knapp ");
            printf("%d", i);
        }
    }
}

void add_call(enum ELEV_STATE *state, MotorDirection *dirn, int call_floor, int *prev_floor, ButtonType btn) {
    // PRIORITIZER//
    int already_in_queue = 0;

    if ((dirn == DIRN_STOP) && (call_floor == elevio_floorSensor())) {
        already_in_queue = 1;
    }

    else if (elevio_stopButton()) {
        already_in_queue = 1; // Ingores calls if sto button is pressed
    }

    for (int i = 0; i < array_size; i++) {

        if ((on_the_way_orders[i] == call_floor) || (cab_orders[i] == call_floor) || (floor_orders[i] == call_floor)) {
            already_in_queue = 1;

            break;
        }
    }

    if (already_in_queue == 0) {

        if (*state == STANDBY || *state == FLOOR_REACHED) {
            if (btn == BUTTON_CAB) {
                add_to(cab_orders, call_floor);
            }
            else if (btn == BUTTON_HALL_DOWN || btn == BUTTON_HALL_UP) {
                add_to(floor_orders, call_floor);
            }
        }

        if (*state == GO_TO) {
            if (btn == BUTTON_CAB) {
                if ((*dirn == DIRN_DOWN) && (call_floor < *prev_floor)) {
                    add_to(on_the_way_orders, call_floor);
                }
                if (((*dirn == DIRN_UP) && (call_floor > *prev_floor))) {
                    add_to(on_the_way_orders, call_floor);
                }
                else {
                    add_to(cab_orders, call_floor);
                }
            }


            else if (btn == BUTTON_HALL_DOWN) {
                if ((*dirn == DIRN_DOWN) && (call_floor < *prev_floor)) {
                    add_to(on_the_way_orders, call_floor);
                }
                else {

                    add_to(floor_orders, call_floor);
                }
            }
            else if (btn == BUTTON_HALL_UP) {
                if ((*dirn == DIRN_UP) && (call_floor > *prev_floor)) {
                    add_to(on_the_way_orders, call_floor);
                }
                else {
                    add_to(floor_orders, call_floor);
                }
            }
        }
    }
}

void print_arrays()
{
    printf("On the way orders:");
    for (int i = 0; i < array_size; i++) {
        printf("|%i|", on_the_way_orders[i]);
    }
    printf("------------------------ \n");
    printf("Cab orders:       ");
    for (int i = 0; i < array_size; i++) {
        printf("|%i|", cab_orders[i]);
    }
    printf("------------------------ \n");
    printf("Floor orders:     ");
    for (int i = 0; i < array_size; i++){
        printf("|%i|", floor_orders[i]);
    }
    printf("------------------------ \n");
}