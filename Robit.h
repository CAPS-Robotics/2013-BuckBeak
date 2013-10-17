/*************************************************************************************
* Robit.h
*
* Declares the main robot class, and the argument structs for each thread
*************************************************************************************/

/*************************************************************************************
Includes
*************************************************************************************/
#include "WPILib.h"

#include "pthread.h"

/*************************************************************************************
Defines
*************************************************************************************/
#define FRONT_RIGHT_MOTOR   2
#define FRONT_LEFT_MOTOR    1
#define BACK_RIGHT_MOTOR    4
#define BACK_LEFT_MOTOR     3

#define COMPRESSOR_PORT     1
#define JOYSTICK_PORT       1
#define PRESSURE_SWITCH     1
#define SHOOTER_PISTON_FORE 1
#define SHOOTER_PISTON_BACK 2
#define TALON_PORT          5

#define AXIS_LEFT_X         1
#define AXIS_LEFT_Y         2
#define AXIS_RIGHT_X        3
#define AXIS_RIGHT_Y        4

#define BTN_A               1

/*************************************************************************************
Main robot class declaration
*************************************************************************************/
class myRobit : public IterativeRobot {
public:
    myRobit();
    ~myRobit();

    void RobotInit();

    void AutonomousInit();
    
    void DisabledInit();
    void TeleopInit();
    void TestInit();

    void DisabledPeriodic();
    void AutonomousPeriodic();
    void TeleopPeriodic();
    void TestPeriodic();
};

/*************************************************************************************
Actuator thread functions
*************************************************************************************/
void * driveFunc( void * );
void * inputFunc( void * );
void * shooterFunc( void * );
