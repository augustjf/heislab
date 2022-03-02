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
void stop();


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