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



/**
 * @brief floor light on
 * 
 */
void floor_light_on();

/**
 * @brief floor button light on 
 * 
 */
void button_light_on(int floor, ButtonType btn);

/**
 * @brief floor light on off, called from floor reached
 * 
 */
void button_light_off(int floor, ButtonType btn);
