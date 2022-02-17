#pragma once 
<<<<<<< HEAD
#include "driver/elevio.h"
#include <time.h>
=======
#include "elevio.h"
>>>>>>> origin/master

/**
 * @file
 * @brief 
 * Library for elevator
 */


/**
 * @brief Structure for holding data for elevator
 * 
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
 * @brief Open door, turn door light on
 * 
 */
void open_door();


/**
 * @brief Close door, turn door light off
 * 
 */
void close_door();