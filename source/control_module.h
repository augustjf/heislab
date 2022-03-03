#pragma once
#include "driver/elevio.h"
#include "elev_module.h"
#include "stdio.h"
#include <string.h>
#include "queue_module.h"
#include "floor_module.h"

/**
 * @file
 * @brief 
 * Library for queue and overall control
 */

typedef struct Order{
    int floor;
    ButtonType btn;
}Order;


/**
 * @brief Elevator states, used in switch to make state machine
 * 
 */
enum ELEV_STATE{
    INIT = 1,
    STANDBY = 2,
    GO_TO = 3,
    FLOOR_REACHED = 4,
    STOP = 5   
}ELEV_STATE;





/**
 * @brief Read stop button from elevator, set motor drive to zero
 * 
 */
void stop(MotorDirection *dirn);


/**
 * @brief Overall control function 
 * 
 */
void run_elevator(enum ELEV_STATE *p_state, MotorDirection *current_dirn, int *prev_floor);

void init_floor(void);

/**
 * @brief Elevator goes to floor based on order from queue 
 * 
 */
void go_to_floor(int floor, int *prev_floor, MotorDirection *dirn);
