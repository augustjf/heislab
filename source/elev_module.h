#pragma once 
#include "driver/elevio.h"
#include <stdio.h>
#include <time.h>

/**
* @file
* @brief Library to control the functions of the elevator itself 
*/

struct elevator
{
    int door;
    int door_obstruction;
    int stop;

    int next_floor;
    int current_floor;

};



/**
 * @brief This function is called when the elevator reaches its destination floor. The function opens the door and 
 * sets a timer for 3 seconds, while it continously checks for obstructions. If there is an obstruction the timer resets.
 * If the timer reaches 3 seconds the door will close.s
 */
void floor_reached();

