#pragma once
#include "driver/elevio.h"
#include "control_module.h"

void add_order(ELEV_STATE state, MotorDirection dirn, int current_floor, int order_floor, ButtonType btn);

void add_to(int arr[], int call);

int next_floor();
