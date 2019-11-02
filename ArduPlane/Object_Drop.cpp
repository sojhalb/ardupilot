#include "Plane.h"
#include <AP_Common/AP_Common.h>
#include <math.h>
#include <AP_HAL/AP_HAL.h>
#include "Object_Drop.h"
#include <utility>
#include <math.h>
#include <AP_Terrain/AP_Terrain.h>
#include <GCS_MAVLink/GCS.h>

#define OUTPUTCH 4
#define INPUTCH 6   

//***most of the code is commented out to test the get_distance() function***



 //Testing out RC INPUTOUTPUT

int Is_Triggered_Glider(uint8_t channel_num){

  //returns 1 if triggered and 0 if not triggered
  bool is_triggered = FALSE;

  //read from the channel and print the pwm value
  uint16_t input = hal.rcin->read(INPUTCH);

  //check value of channel and set to true if there are changes
  if (input > 1750){
      is_triggered = TRUE;
  }

  return is_triggered;
}



void Object_Release(){
    hal.rcout->enable_ch(OUTPUTCH);
    hal.rcout->write(OUTPUTCH, 1800);
}
void Object_Not_Release(){
    hal.rcout->enable_ch(OUTPUTCH);
    hal.rcout->write(OUTPUTCH, 1200);
}

void Plane::calculate_new_drop_location(){
<<<<<<< Updated upstream
=======
    if(next_WP_loc.lat != 0 && next_WP_loc.lon != 0)   {
>>>>>>> Stashed changes



    if(1/*next_WP_loc.lat != 0 && next_WP_loc.lng != 0*/){
        //hal.rcin->enable_ch(INPUTCH);
        uint16_t input = hal.rcin->read(INPUTCH);
      //  int lat1 = current_loc.lat;
       // int lon1 = current_loc.lng;
      //  int lat2 = next_WP_loc.lat; 
      //  int lon2 = next_WP_loc.lng;
        //float airspd = airspeed.get_airspeed();
       // int altitude = current_loc.alt;

        // finding distance

        // to radians = degree * pi/180
<<<<<<< Updated upstream
        //int earth_radius = 6378137;
        //int d= 2*asin(sqrt((sin((lat1-lat2)/2))^2 + cos(lat1)*cos(lat2)*(sin((lon1-lon2)/2))^2));
        //float d = get_distance(current_loc, next_WP_loc);
        float de = get_distance(ahrs.get_home(), current_loc); 

        // radius of target circle
       // int radius = 30;


        //float time = sqrtf(altitude/4.9);
        //float object_distance = airspd * time;         // distance that the dropped thing will land
=======
       // int earth_radius = 6378137;
        //int d= 2*asin(sqrt((sin((lat1-lat2)/2))^2 + cos(lat1)*cos(lat2)*(sin((lon1-lon2)/2))^2));
        float distFromTarget = get_distance(current_location, next_WP_loc);

        // radius of target circle
        int radius = 50;
>>>>>>> Stashed changes


<<<<<<< Updated upstream
        if (((de) >  500) || (input >= 1750)){
            Object_Release();
        } else {
            Object_Not_Release();
        }

        /*
        if( ((d - object_distance) < radius )  && ((d - object_distance) < (radius*-1)) ){
            Object_Release();
        } else if (ahrs.get_home().lat == 0){
            hal.rcout->enable_ch(OUTPUTCH);
             hal.rcout->write(OUTPUTCH, 1600);
        } else if ((de - object_distance) < radius) {
            hal.rcout->enable_ch(OUTPUTCH);
             hal.rcout->write(OUTPUTCH, 1450);
        } else {
            hal.rcout->enable_ch(OUTPUTCH);
            hal.rcout->write(OUTPUTCH, 1400);
        }

        */



    }else {
        Object_Not_Release();
=======
        // if needs to be dropped or not
        if( ( ((distFromTarget - object_distance) < radius ) && ((distFromTarget - object_distance) < (radius*-1)) || Is_Triggered_Glider() ){
        Object_Release();
        }
    }   
    else {
    Object_Not_Release();
>>>>>>> Stashed changes
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
                    Gripper_Release_Service(Need to input waypoint Locations, Glider_Gripper);
                }
            }
             Testing out RC INPUTOUTPUT
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



// CURRENTLY WIP
// TODO: CHECK IF FUNCTIONS ACTUALLY FULFILLS ITS PURPOSE BY DROPPING PAYLOAD

//Reduce risk of collision by dropping at different times
void Plane::glider1_object_drop() {
    calculate_new_drop_location();
}

void Plane::glider2_object_drop() {
    calculate_new_drop_location();
}




