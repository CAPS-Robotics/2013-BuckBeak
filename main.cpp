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
// Debounce for the shooter mechanism
bool spinning = false;
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
	// Compressor relay and pressure limit switch
	Relay compressor;
	DigitalInput clim;
#endif
#ifdef SHOOTER
	// Motor Talons
	Talon sm, si;
	// Fire Solenoid
	Solenoid fo, fi;
	// Index limit switch
	DigitalInput sls;
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
	pto(6),		// Tilt Extended
	compressor(1, Relay::kForwardOnly),		// Compressor relay
	clim(14)	// Pressure limit switch
#endif
#ifdef SHOOTER
	,sm(6),		// Shooter Fire Talon
	si(7),		// Shooter Indexing Talon
	fo(8),		// Shooter Fire out
	fi(7),		// Shooter Fire in
	sls(10)
#endif

	{
#ifdef DRIVE
		// Disable all the Watchdogs
		mDrive.SetSafetyEnabled(false);
#endif
#ifdef SHOOTER
		fo.Set(false);
		fi.Set(true);
#endif
#ifdef PNEUMATICS
		pti.Set(true);
		pto.Set(false);

		plf.Set(false);
		plb.Set(true);
		prf.Set(false);
		prb.Set(true);
#endif
	}
	void Autonomous(void)
	{
#ifdef DRIVE
		// Drive Forwards a ways
		mDrive.MecanumDrive_Cartesian(0,.32,0,0);
		Wait(2.0);
		mDrive.MecanumDrive_Cartesian(0.0,0.0,0.0,0.0);
#endif
#ifdef SHOOTER
		// Spin up, fire, then drop motors
		sm.Set(.5);
		Wait(.32);
		fi.Set(false);
		fo.Set(true);
		Wait(.32);
		fi.Set(true);
		fo.Set(false);
		sm.Set(0.0);
#endif
#ifdef DRIVE
		// Little delay
		Wait(.25);

		// Get ready to drive
		float tempX = .6;
		float tempY = 0.0;
		float tempZ = 0.0;

		// Strafe away
		mDrive.MecanumDrive_Cartesian(tempX, 0.0, tempZ+(tempX*tempRat));

		// Turn around
		Wait(1.9);
		tempZ = .4;
		mDrive.MecanumDrive_Cartesian(0.0, 0.0, tempZ);

		// Drive to midline
		Wait(1.0);
		tempY = .7;
		mDrive.MecanumDrive_Cartesian(0.0, tempY, 0.0);

		// Stop moving
		Wait(2.1);
		mDrive.MecanumDrive_Cartesian(0.0, 0.0, 0.0);
#endif // DRIVE
	}
	void OperatorControl(void)
	{
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
				tempRat += .01; Wait(.2);} // Debounce
			if (stick.GetRawButton(2)){
				tempRat -= .01; Wait(.2);} // Debounce

			// Let the driver know the current mix
			dsPrintFloat(tempRat);
#endif // DEBUG
			smooth(tempX, tempY, tempZ+(tempX*tempRat), &mDrive, 1.5);
#endif // DRIVE

#ifdef PNEUMATICS // MINUS CLIMBING FOR NOW
			/*
			if(stick.GetRawButton(7) && pto.Get()){ // Left trigger climbs
				climb(&stick, &plf, &plb, &prf, &prb, &pti, &pto);
			}

			// Left Bumper deploys the climber
			if(stick.GetRawButton(5)){
				pti.Set(!pti.Get());
				pto.Set(!pto.Get());
			}
			 */
			// If the pressure hasnt been reached, run the compressor
			if(!clim.Get()){
				compressor.Set(Relay::kOn);
			} else {
				compressor.Set(Relay::kOff);
			}
			
			if(stick.GetRawButton(6)){
				compressor.Set(Relay::kOn);
			} else {
				compressor.Set(Relay::kOff);
			}
#endif // PNEUMATICS

#ifdef SHOOTER
			if(stick.GetRawButton(7)){
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

			if(stick.GetRawButton(5)){
				si.Set(-.7);
				while (!sls.Get());
				Wait(.05);
				si.Set(0.0);
			}

			if(stick.GetRawButton(8)){
				spinning = true;
				sm.Set(-1.0);
			} else {
				if (spinning){
					si.Set(-.9);
					while (!sls.Get());
					si.Set(0.0);

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
					spinning = false;
				}
			}
#endif // SHOOTER

#else // SUPERDEBUG
			if(stick.GetRawButton(1)){
				mDrive.MecanumDrive_Cartesian(0.0,.5,0.0);
			} else if(stick.GetRawButton(2)){
				mDrive.MecanumDrive_Cartesian(0.0,-1.0,0.0);
			} else if(stick.GetRawButton(3)){
				mDrive.MecanumDrive_Cartesian(0.0,-.5,0.0);
			} else if(stick.GetRawButton(4)){
				mDrive.MecanumDrive_Cartesian(0.0,1.0,0.0);
			} else {
				mDrive.MecanumDrive_Cartesian(0.0,0.0,0.0);
			}
#endif // SUPERDEBUG
		}
	}
};

// FIRST Macro to start running the program
START_ROBOT_CLASS(RobotDemo);
