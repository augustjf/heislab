#pragma once 
#include "driver/elevio.h"
#include <time.h>

struct elevator
{
    int door;
    int door_obstruction;
    int stop;

    int next_floor;
    int current_floor;

};

/**
 * @brief 
 * 
 */
void open_door();