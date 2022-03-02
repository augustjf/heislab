#pragma once
#include "driver/elevio.h"
#include "control_module.h"
/**
 * @file
 * @brief 
 * Library for floor
 */

/**
 * @brief Structure for holding data for each floor. Each floor have a unique initialization 
 * of the struct
 * 
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

/**
 * @brief floor button light on 
 * 
 */
void floor_button_light_on();

/**
 * @brief floor light on off, called from floor reached
 * 
 */
void floor_button_light_off(Order o);