#pragma once
#include "driver/elevio.h"
#include "control_module.h"

void add_to(int arr[], int call);

int next_floor();

void call_finished(int current_floor);

void add_call(ELEV_STATE state, MotorDirection dirn, int call_floor, int prev_floor, ButtonType btn);



