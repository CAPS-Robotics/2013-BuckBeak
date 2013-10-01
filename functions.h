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
void dsDisplayState(bool);

class Piston{
	Piston(int, int);
	~Piston();
	Solenoid* out;
	Solenoid* in;

	bool Set(bool);
};

#endif
