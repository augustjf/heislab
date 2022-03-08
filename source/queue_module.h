#pragma once
#include "control_module.h"

/**
 * @file
 * @brief 
 * Library for interacting with the queue
 */


/**
 * @brief Delete all orders
 * 
 */
void empty_queue();

/**
 * @brief Add call to chosen array, 
 * 
 */
void add_to(int arr[], int call);

/**
 * @brief Return int for the next floor in the queue, where the elevator shall go next. "On the way orders" are prioritized first, 
 * followed by "Cab orders" and "Floor orders". On the way orders 
 * 
 */
int next_floor();

void call_finished(int current_floor);

void read_buttons(enum ELEV_STATE *state, MotorDirection *dirn, int *prev_floor);

void add_call(enum ELEV_STATE *state, MotorDirection *dirn, int call_floor, int *prev_floor, ButtonType btn);

void print_arrays();


