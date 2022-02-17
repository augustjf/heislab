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
struct Queue{
    int orders[100];
    int ready;          //door closed and ready to move to new floor?
    int elev_floor;
    int state_motor;
    int next_floor;
};


/**
 * @brief Read stop button from elevator, set motor drive to zero
 * 
 */
void stop();
