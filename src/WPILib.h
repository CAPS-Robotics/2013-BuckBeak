/*********************************************************************************//**
* @file WPILib.h
* @author Jacob Hegna
* Header file for mocking the robot API
*************************************************************************************/

#ifndef __WPILIB_H_
#define __WPILIB_H_

/*************************************************************************************
* Defines
*************************************************************************************/
#define                     START_ROBOT_CLASS(a) /**< Entry macro for WPILib        */
#define                     NULL 0

#ifdef _WIN32
typedef int                 UInt32;             /**< VC++ isn't fully C99 compliant */
typedef int                 UInt8;
#endif

/*********************************************************************************//**
* Global functions
*************************************************************************************/
void Wait(float a);

/*********************************************************************************//**
* Non-WPI class that represents all possible WPI enum values
*************************************************************************************/
class ValueClass {                          /**< Normally this is defined in every  */
public:                                     /**< WPI class, we are defining it once */
    enum Value {                            /**< and inheriting it                  */
        kReverse,
        kForward,
        kOn,
        kOff,
        kBoth
    };
};

/*********************************************************************************//**
* Iterative Robot Class
*************************************************************************************/
class IterativeRobot {};

class Compressor {
public:
    Compressor( int a, int b ) {}
    void Start( void ) {}

};

/*********************************************************************************//**
* RobotDrive class
*************************************************************************************/
class RobotDrive {
public:
    RobotDrive( int a, int b, int c, int d ) {}
    void MecanumDrive_Cartesian( float a, float b, float c ) {}
};

/*********************************************************************************//**
* Joystick class
*************************************************************************************/
class Joystick {
public:
    Joystick( int a ) {}
    bool GetRawButton( UInt32 a ) { return false; }
    float GetX() { return 0.f; }
    float GetY() { return 0.f; }
    float GetZ() { return 0.f; }
};

/*********************************************************************************//**
* Talon class
*************************************************************************************/
class Talon : public ValueClass {
public:
    Talon( int a ) {}
    void Set( float a, UInt8 b = 0 ) {}
};

/*********************************************************************************//**
* DoubleSolenoid class
*************************************************************************************/
class DoubleSolenoid : public ValueClass {
public:
    DoubleSolenoid( int a, int b ) {}
    void Set(Value a) {}
};

#endif