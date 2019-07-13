#include "Plane.h"
#include <math.h>
#include <AP_HAL/AP_HAL.h>

#define OUTPUTCH 4
#define INPUTCH = 6;   

                                    //Tracks PWM values. Number of channels unknown

/*
STILL LEFT TODO:
    -find where to access the plane variables
        -**wind
    -Add everything to plane.h + scheduler
*/

/* Testing out RC INPUTOUTPUT
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
*/



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



void Object_Release(){
    hal.rcout->enable_ch(OUTPUTCH);
    hal.rcout->write(OUTPUTCH, 1500);
}

/*
void Plane::control_sequence ()
{
    calculate_new_drop_location();
}
*/

void Plane::calculate_new_drop_location(){
    if(current_location.lat != 0 && current_location.lon != 0 && current_location.alt != 0){

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
