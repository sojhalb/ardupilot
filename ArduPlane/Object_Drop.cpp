#include "Plane.h"
#include <math.h>
#include <AP_HAL/AP_HAL.h>

#define OUTPUTCH 4
#define INPUTCH = 6;   

                                    //Tracks PWM values. Number of channels unknown

/*
STILL LEFT TODO:
*/

/* Testing out RC INPUTOUTPUT

int Is_Triggered_Glider(uint8_t channel_num){
//returns 1 if triggered and 0 if not triggered

  int is_triggered = 0;

  //read from the channel and print the pwm value
  uint16_t input = hal.rcin->read(INPUTCH);

  //check value of channel and set to true if there are changes
  if (input > 1750){
      is_triggered = 1;
  }

  return is_triggered;
}

*/

void Object_Release(){
    hal.rcout->enable_ch(OUTPUTCH);
    hal.rcout->write(OUTPUTCH, 1800);
}
void Object_Not_Release(){
    hal.rcout->enable_ch(OUTPUTCH);
    hal.rcout->write(OUTPUTCH, 1200);
}


void Plane::calculate_new_drop_location(){
    if(next_WP_Loc.lat != 0 && next_WP_Loc.lon != 0){
        /* 
        int lat1 = current_location.lat;
        int lon1 = current_location.lon;
        int lat2 = next_WP_Loc.lat; 
        int lon2 = next_WP_loc.lon;
        int airspeed = airspeed.get_airspeed();
        int altitude = current_location.alt

        // finding distance
        int distance_different;
        // to radians = degree * pi/180
        int earth_radius = 6378137;
        int d= 2*asin(sqrt((sin((lat1-lat2)/2))^2 + cos(lat1)*cos(lat2)*(sin((lon1-lon2)/2))^2));

        // radius of target circle
        int radius = 30;

        // distance that the dropped thing will land
        int time = root(altitude/4.9)
        double object_distance = airspeed * time

        // if needs to be dropped or not
        if( ( ((d - object_distance) < radius ) && ((d - object_distance) < (radius*-1)) || Is_Triggered_Glider() ){
        Object_Release();
        }
        */
       Object_Release();
    }else {
        Object_Not_Release();
    }
}

//enum state_e {IDLE, ARMED};



/* 
void Plane::control_sequence ()
{
    static state_e state = IDLE;
    switch(state)
    {
        case IDLE:
            if(arming.is_armed())
            {
                state = ARMED;
            }
            break;
        case ARMED:
            if(!arming.is_armed())
            {
                state = IDLE;
                break;
            }

            calculate_new_drop_location();
            if(glider.is_drop == false)
            {
                if(current_loc.alt > 50)   //50 feet
                {
                    Object_Release();
                    //Gripper_Release_Service(/*Need to input waypoint Locations, Glider_Gripper);
                }
            }
            /* Testing out RC INPUTOUTPUT
            if(water.is_drop == false)
            {
                if(current_loc.alt > 100)  //100 feet
                {
                    Gripper_Release_Service(//Need to input waypoint Locations, Water_Bottle_Gripper);
                }
            }
            if(nerf.is_drop == false)
            {
                if(current_loc.alt > 100)  //100 feet
                {
                    Gripper_Release_Service(//Need to input waypoint Locations, Nerf_Gripper);
                }
            }
            
            break;
    }
}
*/
/* 
void Plane::update_drop_water ()
{
    if(water.is_drop == false)
        water.is_drop = true;
}
void Plane::update_drop_nerf ()
{
    if(nerf.is_drop == false)
        nerf.is_drop = true;
}
void Plane::update_drop_glider ()
{
    if(glider.is_drop == false)
        glider.is_drop = true;
}
*?
