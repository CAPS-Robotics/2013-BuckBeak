#ifndef __WPILIB_H_
#define __WPILIB_H_

#define START_ROBOT_CLASS(a) 
#define NULL 0

#ifdef _WIN32
typedef int UInt32;
typedef int UInt8;
#endif

void Wait(float a);

class ValueClass {
public:
	enum Value {
		kReverse,
		kForward,
		kOn,
		kOff,
		kBoth
	};
};

class IterativeRobot {};

class Compressor {
public:
	Compressor( int a, int b ) {}
    void Start( void ) {}

};

class RobotDrive {
public:
	RobotDrive( int a, int b, int c, int d ) {}
	void MecanumDrive_Cartesian( float a, float b, float c ) {}
};

class Joystick {
public:
	Joystick( int a ) {}
    bool GetRawButton( UInt32 a ) { return false; }
    float GetX() { return 0.f; }
    float GetY() { return 0.f; }
    float GetZ() { return 0.f; }
};

class Talon : public ValueClass{
public:
	Talon( int a ) {}
    void Set( float a, UInt8 b = 0 ) {}
};

class DoubleSolenoid : public ValueClass {
public:
	DoubleSolenoid( int a, int b ) {}
	void Set(Value a) {}
};

#endif