#pragma once
#include "driver/elevio.h"
#include "control_module.h"

void add_call(ELEV_STATE state, MotorDirection dirn, int prev_floor, int call_floor, ButtonType btn);

void add_to(int arr[], int call);

int next_floor();
