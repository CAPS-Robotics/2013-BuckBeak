 //////////////////////////////////
///////////////////////////////////
/////                         /////
/////     Functions File      /////
/////  Helper Functions here  /////
/////                         /////
///////////////////////////////////
//////////////////////////////////

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void smooth(float, float, float, RobotDrive*, float);
void climb(Joystick*, Solenoid*, Solenoid*, Solenoid*, Solenoid*, Solenoid*, Solenoid*);
void dsPrintFloat(float);
void dsPrintCount(int);

#endif
