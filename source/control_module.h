#pragma once
#include "driver/elevio.h"
/**
 * @file
 * @brief 
 * Library for queue and overall control
 */

/**
 * @brief 
 * Structure for holding array of order and other data related to the elevator
 * and its movement
 */

    //mulige states
typedef enum { 
    INIT   = 0,
    STANDBY   = 1,
    GO_TO = 2,
    FLOOR_REACHED = 3,
    STOP = 4,
} ELEV_STATE;

/**
 * @brief Read stop button from elevator, set motor drive to zero
 * 
 */
int check_stop();


/**
 * @brief Overall control function 
 * 
 */
void run_elevator();

/**
 * @brief Elevator goes to floor based on order from queue 
 * 
 */
void go_to_floor(int floor);