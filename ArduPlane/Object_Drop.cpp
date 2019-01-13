#pragma once

#include "Plane.h"

AP_Gripper_Backend Water_Bottle_Gripper_Backend();
AP_Gripper Water_Bottle_Gripper();

void Fill_Water_Bottle_Config(AP_Gripper &Water_Bottle){
    Water_Bottle.backend = Water_Bottle_Gripper_Backend;
    Water_Bottle.config.type = 1;                            
    Water_Bottle.config.grab_pwm = 1900;                      //Temp values
    Water_Bottle.config.release_pwm = 1100;                   //Temp values
    Water_Bottle.config.neutral_pwm = 1500;                   //Temp values
    Water_Bottle.config.regrab_interval = 3;                  //Temp values
}

void Set_Water_Bottle_Release_Waypoint(){

}
//Starting Point?
//have to change code to make water, nerf, and glider known to program
enum state_e {IDLE, ARMED};

void control_sequence ()
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
                if(plane.posy>50 && glider.glider_drop_area() && (glider.within_drop_range() || glider.is_moving_away_from_drop()))//50 feet
                {
                    glider.drop();
                    plane.update_drop_glider();
                }
            }
            if(water.is_drop == false)
            {
                if(plane.posy>100 && (water.within_drop_range() || water.is_moving_away_from_drop()))//100 feet
                {
                    water.drop();
                    plane.update_drop_water();
                }
            }
            if(nerf.is_drop == false)
            {
                if(plane.posy>100 && (nerf.within_drop_range() || nerf.is_moving_away_from_drop()))//100 feet
                {
                    nerf.drop();
                    nerf.update_drop_nerf();
                }
            }
            break;
    }
}
void update_drop_water () 
{
    if(water.is_drop == false)
        water.is_drop = true;
}
void update_drop_nerf () 
{
    if(nerf.is_drop == false)
        nerf.is_drop = true;
}
void update_drop_glider () 
{
    if(glider.is_drop == false)
        glider.is_drop = true;
}
void calculate_new_drop_location()
{}