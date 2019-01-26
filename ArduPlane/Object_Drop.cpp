
#pragma once

#include "Plane.h"
#include <math.h>

AP_Gripper_Backend Water_Bottle_Gripper_Backend();
AP_Gripper Water_Bottle_Gripper();

AP_Gripper_Backend _Gripper_Backend();
AP_Gripper _Gripper();

AP_Gripper_Backend Glider_Gripper_Backend();         
AP_Gripper Glider_Gripper();

double Water_Range_X = 0.5;                                         //Temp values
double Water_Range_Y = 0.5;                                         //Temp values
double Water_Range_Z = 0.5;                                         //Temp values

double _Range_X = 0.5;                                              //Temp values
double _Range_Y = 0.5;                                              //Temp values
double _Range_Z = 0.5;                                              //Temp values

double Glider_Range_X = 0.5;                                        //Temp values
double Glider_Range_Y = 0.5;                                        //Temp values
double Glider_Range_Z = 0.5;                                        //Temp values

void Fill_Water_Bottle_Config(AP_Gripper &Water_Bottle){
    Water_Bottle.backend = Water_Bottle_Gripper_Backend;
    Water_Bottle.config.type = 1;                            
    Water_Bottle.config.grab_pwm = 1900;                            //Temp values
    Water_Bottle.config.release_pwm = 1100;                         //Temp values
    Water_Bottle.config.neutral_pwm = 1500;                         //Temp values
    Water_Bottle.config.regrab_interval = 3;                        //Temp values
}

void Fill__Config(AP_Gripper &){
    .backend = _Gripper_Backend;
    .config.type = 1;                            
    .config.grab_pwm = 1900;                                        //Temp values
    .config.release_pwm = 1100;                                     //Temp values
    .config.neutral_pwm = 1500;                                     //Temp values
    .config.regrab_interval = 3;                                    //Temp values
}

void Fill_Glider_Config(AP_Gripper &Water_Bottle){
    Glider.backend = Glider_Gripper_Backend;
    Glider.config.type = 1;                             
    Glider.config.grab_pwm = 1900;                                  //Temp values
    Glider.config.release_pwm = 1100;                               //Temp values
    Glider.config.neutral_pwm = 1500;                               //Temp values
    Glider.config.regrab_interval = 3;                              //Temp values
}

void Gripper_Release_Service(double Current_X_Position, double Current_Y_Position, double Current_Z_Position,
                                 double Drop_X_Position, double Drop_Y_Position, double Drop_Z_Position,
                                    AP_Gripper &Gripper){

    if (abs(Current_X_Position, Drop_X_Position) < Range_X &&
          abs(Current_Y_Position, Drop_Y_Position) < Range_Y &&
             abs(Current_Z_Position, Drop_Z_Position) < Range_Z){
                Gripper.release();
    }
}





