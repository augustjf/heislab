
#include "queue_module.h"

void stop(){
    int stop_yn = elevio_stopButton();
    if(stop_yn == 1){
        elevio_stopLamp(1);
        elevio_motorDirection(0);
        
    } 
}

void run_elevator(){

    //mulige states
    typedef enum { 
    INIT   = 0,
    STANDBY   = 1,
    FLOOR_REACHED = 2,
    STOP = 3,
    } ELEV_STATE;
    
    
    //looper gjennom
    while(1) {
        ELEV_STATE state = INIT;  //settes automatisk til init

        if(elevio_stopButton() == 1){  //må alltid sjekke om det er stop
            state = STOP;
        }

        switch(state){
            case INIT:
                //statement
                break;

            

            default:
                break;
        }
    
    }

}