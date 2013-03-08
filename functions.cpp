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
	dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "%.3f:%.3f:%.3f", tX, tY, tZ);	// Desired
	dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "%.3f:%.3f:%.3f", cX, cY, cZ);	// Current
	dsLCD->UpdateLCD();
#endif

	// Actually doo dat drive thang
	rDrive->MecanumDrive_Cartesian(cX, cY, cZ);
}

// Climb sequence
// Runs through the whole shabang before returning
// Right out, Left out, Both in
void climb(Joystick* mJoy, Solenoid* slo, Solenoid* sli, Solenoid* sro, Solenoid* sri, Solenoid* sti, Solenoid* sto){
	int i, step;
	step = 1;
	bool kill = false;

	Wait(.25);

	for (i=1;i<5;i++){

		sri->Set(false);
		sli->Set(false);
		sro->Set(true);
		slo->Set(true);

		while(1){
#ifdef DEBUG
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "%d / 9", step);
			dsLCD->UpdateLCD();
#endif
			if(mJoy->GetRawButton(7)){
				kill = true;
				break;
			}
			if(mJoy->GetRawButton(5)){
				break;
			}
		}
		if (kill) break;

		if(step == 1){
			Wait(1.0);
			step++;
			
			sto->Set(false);
			sti->Set(true);
			
			while (1){
#ifdef DEBUG
				dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "%d / 9", step);
				dsLCD->UpdateLCD();
#endif
				if(mJoy->GetRawButton(7)){
					kill = true;
					break;
				}
				if(mJoy->GetRawButton(5)){
					break;
				}
			}
		}

		sro->Set(false);
		slo->Set(false);
		sri->Set(true);
		sli->Set(true);

		Wait(1.0);
		step++;

		while(1){
#ifdef DEBUG
			dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "%d / 9", step);
			dsLCD->UpdateLCD();
#endif
			if (mJoy->GetRawButton(7)){
				kill = true;
				break;
			}
			if (mJoy->GetRawButton(5)){
				break;
			}
		}
		if (kill) break;

		Wait(1.0);
		step++;
	}
#ifdef DEBUG
	dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "DONE       "); 
	dsLCD->UpdateLCD();
#endif

	sro->Set(false);
	slo->Set(false);
	sri->Set(true);
	sli->Set(true);
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
