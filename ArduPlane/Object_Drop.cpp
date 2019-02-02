#pragma once
#include "Plane.h"
#include <math.h>

/*
STILL LEFT TODO:
    -calculate ideal drop location + get lat/lng/alt values every loop
        -Create a drop Location location (class)
        -**wind
    -set defininte ranges (or create a function to vary ranges)
    -Add everything to plane.h + scheduler
    -Generate waypoint on Ardupilot
*/

AP_GPS* gps = plane.get_gps();
const Location* location = gps->location();
location.latitude;

AP_Gripper_Backend Water_Bottle_Gripper_Backend;
AP_Gripper Water_Bottle_Gripper;

AP_Gripper_Backend Nerf_Gripper_Backend;
AP_Gripper Nerf_Gripper;

AP_Gripper_Backend Glider_Gripper_Backend;         
AP_Gripper Glider_Gripper;

double Water_Range_lat = 0.5;                                         //Temp values
double Water_Range_lng = 0.5;                                         //Temp values
double Water_Range_alt = 0.5;                                         //Temp values

double Nerf_Range_lat = 0.5;                                              //Temp values
double Nerf_Range_lng = 0.5;                                              //Temp values
double Nerf_Range_alt = 0.5;                                              //Temp values

double Glider_Range_lat = 0.5;                                        //Temp values
double Glider_Range_lng = 0.5;                                        //Temp values
double Glider_Range_alt = 0.5;                                        //Temp values

void Fill_Water_Bottle_Config(AP_Gripper &Water_Bottle){
    Water_Bottle.backend = Water_Bottle_Gripper_Backend;
    Water_Bottle.config.type = 1;                            
    Water_Bottle.config.grab_pwm = 1900;                            //Temp values
    Water_Bottle.config.release_pwm = 1100;                         //Temp values
    Water_Bottle.config.neutral_pwm = 1500;                         //Temp values
    Water_Bottle.config.regrab_interval = 3;                        //Temp values
}

void Fill_Nerf_Config(AP_Gripper &Nerf){
    Nerf.backend = Nerf_Gripper_Backend;
    Nerf.config.type = 1;                            
    Nerf.config.grab_pwm = 1900;                                        //Temp values
    Nerf.config.release_pwm = 1100;                                     //Temp values
    Nerf.config.neutral_pwm = 1500;                                     //Temp values
    Nerf.config.regrab_interval = 3;                                    //Temp values
}

void Fill_Glider_Config(AP_Gripper &Glider){
    Glider.backend = Glider_Gripper_Backend;
    Glider.config.type = 1;                             
    Glider.config.grab_pwm = 1900;                                  //Temp values
    Glider.config.release_pwm = 1100;                               //Temp values
    Glider.config.neutral_pwm = 1500;                               //Temp values
    Glider.config.regrab_interval = 3;                              //Temp values
}

void Plane::Glider_Release_Service(double Drop_lat_Position, double Drop_lng_Position, double Drop_alt_Position){
    if ((abs(current_loc.lat, Drop_lat_Position) < Glider_Range_lat && abs(current_loc.lng, Drop_lng_Position) < Glider_Range_lng &&
             abs(current_loc.alt, Drop_alt_Position) < Glider_Range_alt) || Glider.is_moving_Away_from_drop()) {
                Gripper.release();
                Plane.update_drop_glider();
    }
}

void Plane::Water_Bottle_Release_Service(double Drop_lat_Position, double Drop_lng_Position, double Drop_alt_Position){
    if ((abs(current_loc.lat, Drop_lat_Position) < Water_Range_lat && abs(current_loc.lng, Drop_lng_Position) < Water_Range_lng &&
             abs(current_loc.alt, Drop_alt_Position) < Water_Range_alt) || Water_Bottle_Gripper.is_moving_away_from_drop()) {
                Gripper.release();
                Plane.update_drop_water();
    }
}

void Plane::Nerf_Release_Service(double Drop_lat_Position, double Drop_lng_Position, double Drop_alt_Position){
    if ((abs(current_loc.lat, Drop_lat_Position) < Nerf_Range_lat && abs(current_loc.lng, Drop_lng_Position) < Nerf_Range_lng &&
             abs(current_loc.alt, Drop_alt_Position) < Nerf_Range_alt) || Nerf_Gripper.is_moving_away_from_drop()) {
                Gripper.release();
                Plane.update_drop_nerf();
    }
}
//Starting Point?
//have to change code to make water, nerf, and glider known to program



enum state_e {IDLE, ARMED};

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
                    Gripper_Release_Service(/*Need to input waypoint Locations*/, Glider_Gripper);
                }
            }
            if(water.is_drop == false)
            {
                if(current_loc.alt > 100)  //100 feet
                {
                    Gripper_Release_Service(/*Need to input waypoint Locations*/, Water_Bottle_Gripper);
                }
            }
            if(nerf.is_drop == false)
            {
                if(current_loc.alt > 100)  //100 feet
                {
                    Gripper_Release_Service(/*Need to input waypoint Locations*/, Nerf_Gripper);
                }
            }
            break;
    }
}
void Set_Water_Bottle_Release_Waypoint(){}

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

void calculate_new_drop_location()
{}
