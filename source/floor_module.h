#pragma once
#include "driver/elevio.h"

/**
 * @file
 * @brief 
 * Library for floor
 */

struct Floor{
    int this_floor;  
    int floor_btn;

    int bool_floor_light;
    int bool_elev_on_floor;

};



/**
 * @brief floor light on
 * 
 */
void floor_light_on();