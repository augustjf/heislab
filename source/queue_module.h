#pragma once
#include "control_module.h"



void empty_queue();

void add_to(int arr[], int call);

int next_floor();

void call_finished(int current_floor);

void read_buttons(enum ELEV_STATE *state, MotorDirection *dirn, int *prev_floor);

void add_call(enum ELEV_STATE *state, MotorDirection *dirn, int call_floor, int *prev_floor, ButtonType btn);

void print_arrays();


