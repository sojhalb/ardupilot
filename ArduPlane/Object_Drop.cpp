#include "Plane.h"
#include <math.h>
#include <AP_HAL/HAL.h>

#define OUTPUTCH 5
#define INPUTCH 6

static uint16_t output_last_value = -1;


static uint16_t pwm = 1500;
static int8_t delta = 1;

int Is_Triggered_Glider();

void Plane::Object_Release(){

    hal.rcout->enable_ch(OUTPUTCH);

    hal.rcout->write(OUTPUTCH, pwm);
    
    if (Is_Triggered_Glider()){
        pwm = 1000;
    }

    if (pwm >= 2000) {
        //do nothing    
    } else {
        pwm += delta;
    }
}

int Is_Triggered_Glider(){
//returns 1 if triggered and 0 if not triggered

  int is_triggered = 0;

  //read from the channel and print the pwm value
  uint16_t input = hal.rcin->read(INPUTCH);

  //check value of channel and set to true if there are changes
  if (output_last_value == -1){
      output_last_value = input;
  }

  if (input != output_last_value) {
    output_last_value = input;
    is_triggered = 1;
  }
  
  return is_triggered;
}
