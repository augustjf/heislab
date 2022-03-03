#pragma once
#include "driver/elevio.h"
#include "elev_module.h"
#include "stdio.h"
/**
 * @file
 * @brief 
 * Library for queue and overall control
 */


/**
 * @brief Elevator states, used in switch to make state machine
 * 
 */

enum ELEV_STATE{ 
    INIT,
    STANDBY,
    GO_TO,
    FLOOR_REACHED,
    STOP,
};

typedef struct{
    int floor;
    ButtonType btn;
}Order;


/**
 * @brief Read stop button from elevator, set motor drive to zero
 * 
 */
void stop();


/**
 * @brief Overall control function 
 * 
 */
void run_elevator(enum ELEV_STATE state);

/**
 * @brief Elevator goes to floor based on order from queue 
 * 
 */
void go_to_floor(int floor);

Order read_buttons();