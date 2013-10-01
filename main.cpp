 /////////////////////////////////
//////////////////////////////////
/////                        /////
/////     Main Code File     /////
/////                        /////
//////////////////////////////////
/////////////////////////////////

#include "WPILib.h"
#include "math.h"
#include "config.h"
#include "functions.h"

// Strafe Mixing value (compensates for offset back wheels)
float tempRat = -0.13;
// Counter for number of times shot
int shotcount = 0;

class RobotDemo : public SimpleRobot
{
	// MUST BE A GAMEPAD
	Joystick stick;
#ifdef DRIVE
	// Drivebase
	RobotDrive mDrive;
#endif
#ifdef PNEUMATICS
	// Climbing Solenoids
	Solenoid plf, plb, prf, prb, pti, pto;
#endif
#ifdef SHOOTER
	// Motor Talons
	Talon sm, si;
	// Fire Solenoid
	Solenoid fo, fi;
	// Index limit switch
	DigitalInput sls;
#endif
#ifdef COMPRESSOR
	// Compressor class
	Compressor comp;
#endif
#ifdef TESTING
	// Stuff goes here
#endif
public:
	RobotDemo(void):
		// MANDATORY: GAMEPAD
		stick(1)
#ifdef DRIVE
	// Order is: FL, BL, FR, BR
	,mDrive(1,3,2,4)
#endif
#ifdef PNEUMATICS
	,plf(1),	// Left Forwards
	plb(2),		// Left Backwards
	prf(3),		// Right Forwards
	prb(4),		// Right Backwards
	pti(5),		// Tilt Retracted
	pto(6)		// Tilt Extended
#endif
#ifdef SHOOTER
	,sm(6),		// Shooter Fire Talon
	si(7),		// Shooter Indexing Talon
	fo(8),		// Shooter Fire out
	fi(7),		// Shooter Fire in
	sls(10)		// Limit switch
#endif
#ifdef COMPRESSOR
	,comp(13, 3)	// Compressor
#endif
#ifdef TESTING
	// Init stuff here
#endif
	{
#ifdef DRIVE
		// Disable all the Watchdogs
		mDrive.SetSafetyEnabled(false);
#endif
#ifdef SHOOTER
		// Initial Solenoid Values
		fo.Set(false);
		fi.Set(true);
#endif
#ifdef PNEUMATICS
		// Initial Solenoid Values
		pti.Set(true);
		pto.Set(false);

		plf.Set(false);
		plb.Set(true);
		prf.Set(false);
		prb.Set(true);
#endif
#ifdef TESTING
		// Init functions go here
#endif
	}
	void Autonomous(void)
	{
#ifndef SUPERDEBUG
#ifdef AUTOMODE
#ifdef DRIVE
		// Drive Forwards a ways
		mDrive.MecanumDrive_Cartesian(0,.5,.15,0);
		Wait(1.45);
		mDrive.MecanumDrive_Cartesian(0.0,0.0,0.0,0.0);
#endif
#ifdef SHOOTER
		
//		float shottime;
	
		// Spin up, fire, then drop motors

		sm.Set(-1.0);

		Wait(1.25);

		fi.Set(false);
		fo.Set(true);
		Wait(.5);
		fo.Set(false);
		fi.Set(true);
		shotcount += 1;
		dsPrintCount(shotcount);

		Wait(.75);

		si.Set(-.7);
		// WARNING:
		// The while can lock up the robot for a whole match
//		shottime = GetTime();
//		while (!sls.Get() && (GetTime() - shottime) >= 1.0);
		Wait(.75);
		Wait(.05);
		si.Set(0.0);

		Wait(1.25);

		fi.Set(false);
		fo.Set(true);
		Wait(.5);
		fo.Set(false);
		fi.Set(true);
		shotcount += 1;
		dsPrintCount(shotcount);
/*
		si.Set(-.7);
		// WARNING:
		// The while can lock up the robot for a whole match
		shottime = GetTime();
		while (!sls.Get() && (GetTime() - shottime) >= 1.0);
		Wait(.05);
		si.Set(0.0);

		Wait(1.25);

		fi.Set(false);
		fo.Set(true);
		Wait(.5);
		fo.Set(false);
		fi.Set(true);
		shotcount += 1;
		dsPrintCount(shotcount);
*/
		sm.Set(0.0);
#endif // SHOOTER

#endif // AUTOMODE
#endif // SUPERDEBUG CONTROL
	}
	void OperatorControl(void)
	{
#ifdef COMPRESSOR
		comp.Start();
#endif
		while (IsOperatorControl())
		{
#ifndef SUPERDEBUG
#ifdef DRIVE
			// Deadzones, and power scaling
			float tempX = (fabs(stick.GetRawAxis(3)) > .2)?-stick.GetRawAxis(3)*.75:0.0;
			float tempY = (fabs(stick.GetRawAxis(2)) > .2)?-stick.GetRawAxis(2)*.9:0.0;
			// Z input is scaled, then squared. It has no deadzone
			float tempZ = pow((-stick.GetRawAxis(1)*.8),2)*((stick.GetRawAxis(1) > 0)?-1.0:1.0);

#ifdef DEBUG
			// Increment or decrement the strafe mixing value
			if (stick.GetRawButton(4)){
				tempRat += .01; Wait(.2); // Debounce
				// Let the driver know the current mix
				dsPrintFloat(tempRat);}
			if (stick.GetRawButton(2)){
				tempRat -= .01; Wait(.2); // Debounce
				// Let the driver know the current mix
				dsPrintFloat(tempRat);}
#endif // DEBUG
			// Actually drive the robot
			smooth(tempX, tempY, tempZ+(tempX*tempRat), &mDrive, 1.5);
#endif // DRIVE

#ifdef PNEUMATICS
			if(stick.GetRawButton(7)){ // Left trigger extends
				prf.Set(true);
				plf.Set(true);
				prb.Set(false);
				plb.Set(false);

				if(pti.Get()){
					pti.Set(false);
					pto.Set(true);
					Wait(.2);
				}
			} else { // Only while held
				prb.Set(true);
				plb.Set(true);
				prf.Set(false);
				plf.Set(false);
			}

			// Left Bumper deploys the climber
			if(stick.GetRawButton(5)){
				pti.Set(!pti.Get());
				pto.Set(!pto.Get());
				dsDisplayState(pto.Get());
				Wait(.2);
			}
#endif // PNEUMATICS

#ifdef SHOOTER
			if(stick.GetRawButton(8)){ // Right trigger fires
				sm.Set(-1.0);

				Wait(1.25);

				fi.Set(false);
				fo.Set(true);
				Wait(.5);
				fo.Set(false);
				fi.Set(true);
				shotcount += 1;
				dsPrintCount(shotcount);

				Wait(.75);

				sm.Set(0.0);
			}

			if(stick.GetRawButton(6)){ // Right bumper loads a disc
				Wait(.2);
				si.Set(-.7);
				// WARNING:
				// The while can lock up the robot for a whole match
				while (!sls.Get());
				Wait(.05);
				si.Set(0.0);
			}
#endif // SHOOTER

#else // SUPERDEBUG
			if(stick.GetRawButton(1)){
				mDrive.MecanumDrive_Cartesian(0.0,.5,0.0);
#ifdef SHOOTER
				sm.Set(0.5);
				si.Set(0.5);
#endif
			} else if(stick.GetRawButton(2)){
				mDrive.MecanumDrive_Cartesian(0.0,-1.0,0.0);
#ifdef SHOOTER
				sm.Set(-1.0);
				si.Set(-1.0);
#endif
			} else if(stick.GetRawButton(3)){
				mDrive.MecanumDrive_Cartesian(0.0,-.5,0.0);
#ifdef SHOOTER
				sm.Set(-0.5);
				si.Set(-0.5);
#endif
			} else if(stick.GetRawButton(4)){
				mDrive.MecanumDrive_Cartesian(0.0,1.0,0.0);
#ifdef SHOOTER
				sm.Set(1.0);
				si.Set(1.0);
#endif
			} else {
				mDrive.MecanumDrive_Cartesian(0.0,0.0,0.0);
#ifdef SHOOTER
				sm.Set(0.0);
				si.Set(0.0);
#endif
			}
#endif // SUPERDEBUG

#ifdef TESTING
			// Teleop goes here
#endif
		}
#ifdef COMPRESSOR
		comp.Stop();
#endif
	}
};

// FIRST Macro to start running the program
START_ROBOT_CLASS(RobotDemo);
