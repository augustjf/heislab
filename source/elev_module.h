#pragma once 

struct elevator
{
    bool door;
    bool door_obstruction;
    bool stop;

    int next_floor;
    int current_floor;

};

/**
 * @brief 
 * 
 */
void open_door();