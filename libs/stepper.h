#include <wiringPi.h>
#include <iostream>
#include <time.h>
#include <cmath>
#include <ctime>

void CW_rotation();

void CCW_rotation();

void stepper_1step();

void step_day_light(time_t t, tm* tPtr, float lat, int &rise_time, int &time_between_steps);

void do_steps(time_t t, tm* tPtr, float lat, int &rise_time, int& temp_rise_time, int& time_between_steps);