 //////////////////////////////////
///////////////////////////////////
/////                         /////
/////     Functions File      /////
/////  Helper Functions here  /////
/////                         /////
///////////////////////////////////
//////////////////////////////////

#include "WPILib.h"
#include "math.h"
#include "config.h"
#include "functions.h"

#ifdef DEBUG
// Set up the DS
DriverStationLCD* dsLCD = DriverStationLCD::GetInstance();
#endif

// Uses time smoothing to simulate acceleration
// Still not sure exactly what GetTime returns though...
void smooth(float tX, float tY, float tZ, RobotDrive *rDrive, float smotFact){
	// Static starting time, updated each tick
	static double ctime = GetTime();
	// Time at current tick
	double ntime = GetTime();

	// Max allowable acceleration
	float accelFact = (ntime - ctime) * smotFact;
	// Current output values
	static float cX, cY, cZ;

	// If change greater than max allowed, only increment, else just set
	if(fabs(cX - tX) > accelFact){cX += (tX < cX)?-accelFact:accelFact;} else {cX = tX;}
	if(fabs(cY - tY) > accelFact){cY += (tY < cY)?-accelFact:accelFact;} else {cY = tY;}
	if(fabs(cZ - tZ) > accelFact){cZ += (tZ < cZ)?-accelFact:accelFact;} else {cZ = tZ;}

	// Update current time
	ctime = ntime;

#ifdef DEBUG
	// Print out current and desired output to the DS 
//	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "%.3f:%.3f:%.3f", tX, tY, tZ);	// Desired
//	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "%.3f:%.3f:%.3f", cX, cY, cZ);	// Current
	dsLCD->UpdateLCD();
#endif

	// Actually doo dat drive thang
	rDrive->MecanumDrive_Cartesian(cX, cY, cZ);
}

// Climb sequence
// Runs through the whole shabang before returning
// Right out, Left out, Both in
void climb(Joystick* mJoy, Solenoid* slo, Solenoid* sli, Solenoid* sro, Solenoid* sri, Solenoid* sti, Solenoid* sto){
}

// Prints a float to line 5.
// Simple as that
void dsPrintFloat(float val){
#ifdef DEBUG
	dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Mix value: %.3f", val);
#endif
}

// Prints the count to line 4
// Simple as that
void dsPrintCount(int val){
#ifdef DEBUG
	dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Count: %d ", val);
#endif
}

// Prints the state of the climber
// Ternary operators FTW!
void dsDisplayState(bool tf){
#ifdef DEBUG
	dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, (tf)?"Deployed ":"Retracted");
#endif
}

// Piston class
// Designed to make things simpler
// Constructor
Piston::Piston(int o, int i){
	out = new Solenoid(o);
	in = new Solenoid(i);
}

// Destructor
Piston::~Piston(){}

bool Piston::Set(bool io){
	out->Set(io);
	in->Set(!io);
	return !io;
}
