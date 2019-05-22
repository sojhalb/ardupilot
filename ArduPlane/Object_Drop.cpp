#pragma once
#include "Plane.h"
#include <math.h>
#include <AP_HAL/AP_HAL.h>

#define OUTPUTCH 4

const AP_HAL::HAL& hal = AP_HAL::get_HAL();

static uint16_t pwm = 1500;
static int8_t delta = 1;


void Plane::Object_Release(){

    hal.rcout->enable_ch(OUTPUTCH);

    hal.rcout->write(OUTPUTCH, pwm);
    pwm += delta;

    if (delta > 0 && pwm >= 2000) {
        delta = -1;
    } else if (delta < 0 && pwm <= 1000) {
        delta = 1;
    }

    hal.scheduler->delay(5);

}

AP_HAL_MAIN();