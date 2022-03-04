#include "queue_module.h"

//Make function to increase array size if needed
int on_the_way_orders[20]; //orders coming from a floor as the cab is moving in that direction
int cab_orders[20]; //orders from the cab, initialized to 50
int floor_orders[20]; //orders form the floors
int array_size = 20;

void empty_queue() {
    for (int i = 0; i < array_size; i++) {
        on_the_way_orders[i] = -1;
        cab_orders[i] = -1;
        floor_orders[i] = -1;
    }
}

void add_to(int arr[], int call) {

    printf("|inne i add to...|");
    for (int i = 0; i < array_size; i++) {
        if (arr[i] == -1) {
            arr[i] = call;
            break;
        }
    }
   
}

void call_finished(int current_floor) {
    int temp[array_size];
    if (on_the_way_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            temp[i] = on_the_way_orders[i];
        }
        for (int i = 0; i < (array_size - 1); i++) {
            on_the_way_orders[i] = temp[i+1];
        }
    }    
    else if (cab_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            temp[i] = cab_orders[i];
        }
        for (int i = 0; i < (array_size - 1); i++) {
            cab_orders[i] = temp[i+1];
        }
    }
    else if (floor_orders[0] == current_floor) {
        for (int i = 0; i < (array_size - 1); i++) {
            temp[i] = floor_orders[i];
        }
        for (int i = 0; i < (array_size - 1); i++) {
            floor_orders[i] = temp[i+1];
        }
    }
}

int next_floor() {

    if (on_the_way_orders[0] != -1) {
        return on_the_way_orders[0];
    }
    if ((cab_orders[0] != -1) && (on_the_way_orders[0] == -1)) {
        return cab_orders[0];
    }
    if ((floor_orders[0] != -1) && (cab_orders[0] == -1) && (on_the_way_orders[0] == -1)) {
        return floor_orders[0];
    }
    else{
        return -1;
    }
}



void read_buttons(enum ELEV_STATE *state, MotorDirection *dirn, int *prev_floor) {
    for(int i = 0; i < 4; i++){
        if(elevio_callButton(i, BUTTON_HALL_UP) == 1){
            printf("read 1");
            add_call(state, dirn, i, prev_floor, BUTTON_HALL_UP);
            button_light_on(i, BUTTON_HALL_UP);
        }
        else if(elevio_callButton(i, BUTTON_HALL_DOWN) == 1){
            printf("read 2");
            add_call(state, dirn, i, prev_floor, BUTTON_HALL_DOWN);
            button_light_on(i, BUTTON_HALL_DOWN);
        }
        else if(elevio_callButton(i, BUTTON_CAB) == 1){
            printf("read 3");
            add_call(state, dirn, i, prev_floor, BUTTON_CAB);
            button_light_on(i, BUTTON_CAB);

                printf("knapp  ");
                printf("%d", i );
        

        }
        printf("-");
    }

}



void add_call(enum ELEV_STATE *state, MotorDirection *dirn, int call_floor, int *prev_floor, ButtonType btn) {
    //PRIORITIZER//
    int already_in_queue = 0;
    
    printf("add call");

    for (int i = 0; i < array_size; i++) {
        if ((dirn == DIRN_STOP) && (*prev_floor == elevio_floorSensor())) {
            already_in_queue = 1;

        
            break;
        }
        else if((on_the_way_orders[i] == call_floor) || (cab_orders[i] == call_floor) || (floor_orders[i] == call_floor)) {
            already_in_queue = 1;
         



            break;
        }
        else if (elevio_stopButton()) {
            already_in_queue = 1; //Ingores calls if sto button is pressed

          
        }
        else {
            already_in_queue = 0;
        }
     
        
    }
    if(*state == STANDBY){
        printf(" standby ");
    }
    if(*state == GO_TO){
        printf(" go to ");
    }
    if(*state == FLOOR_REACHED){
        printf(" floor reached ");
    }

    if(already_in_queue == 0) {
        printf(" inne i alfready in q ");
        
        if (*state == STANDBY || *state == FLOOR_REACHED) {
            if (btn == BUTTON_CAB) { 
                
                if(btn == BUTTON_CAB){
                    printf(" btn_cab ");
                }
                printf("  add to 1"  );

                add_to(cab_orders, call_floor);
               
                
            }
            else if (btn == BUTTON_HALL_DOWN || btn == BUTTON_HALL_UP) {
               
                printf("  add to 2"  ); 
                add_to(floor_orders, call_floor);
            }

            //on_the_way_orders cannot happen in STANDBY
        }

        if (*state == GO_TO) {
            if (btn == BUTTON_CAB) {
                
                 printf("  add to 3"  );
                 add_to(cab_orders, call_floor);
            }
            else if (btn == BUTTON_HALL_DOWN) {
                if ((*dirn == DIRN_DOWN) && (call_floor < *prev_floor)) {
                    printf("  add to 4"  ); 
                    add_to(on_the_way_orders, call_floor);
                    
                }
                else {
                    printf("  add to 5"  );
                    add_to(floor_orders, call_floor);
                }     

            }
            else if (btn == BUTTON_HALL_UP) {
                if ((*dirn == DIRN_UP) && (call_floor > *prev_floor)) {
                     printf("  add to 6"  );
                    add_to(on_the_way_orders, call_floor);
                    
                }
                else {
                    printf("  add to 7"  );
                    add_to(floor_orders, call_floor);
                    
                }
            }
        }
    }
}

void print_arrays() {
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
    for (int i = 0; i < array_size; i++) {
        printf("|%i|", floor_orders[i]);
    }
    printf("------------------------ \n");
}