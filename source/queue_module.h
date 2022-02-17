#pragma once

struct Queue{
    int orders[100];
    bool ready;
    int elev_floor;
    int state_motor;
    int next_floor;
};


/**
 * @brief Read stop button from elevator, set motor drive to zero
 * 
 */
void stop();
