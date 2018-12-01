#pragma once

#include "plane.h"

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

Void Set_Water_Bottle_Release_Waypoint(){

}

