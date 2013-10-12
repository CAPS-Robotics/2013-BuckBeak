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
#include "semaphore.h"

/*************************************************************************************
Defines
*************************************************************************************/
#define FRONT_RIGHT_MOTOR	1
#define FRONT_LEFT_MOTOR	2
#define BACK_RIGHT_MOTOR	3
#define BACK_LEFT_MOTOR		4

#define COMPRESSOR_PORT		6
#define JOYSTICK_PORT		1
#define PRESSURE_SWITCH		1
#define SHOOTER_PISTON_FORE	1
#define SHOOTER_PISTON_BACK	2
#define TALON_PORT			5

#define AXIS_LEFT_X			1
#define AXIS_LEFT_Y			2
#define AXIS_RIGHT_X		3
#define AXIS_RIGHT_Y		4

#define BTN_A				1

/*************************************************************************************
Main robot class declaration
*************************************************************************************/
class myRobit : public IterativeRobot {
public:
	myRobit();
	~myRobit();

	void RobotInit();

	void AutonomousInit();

private:
	pthread_t			driveThread;
	pthread_t			inputThread;
	pthread_t			shooterThread;

	Compressor *		compressor;			/* Compressor for pneumatics			*/
	RobotDrive *		drivetrain;			/* Drivetrain - Mecanum					*/
	Joystick *			joystick;			/* Joystick for input					*/
	Talon *				shooter_motor;		/* CIM for shooting						*/
	DoubleSolenoid *	shooter_piston;		/* Piston for firing discs				*/
};

/*************************************************************************************
Actuator thread functions
*************************************************************************************/
void * driveFunc( void * );
void * inputFunc( void * );
void * shooterFunc( void * );

/*************************************************************************************
Drive thread argument
*************************************************************************************/
struct drive_arg {
	RobotDrive *		drivetrain;
	Joystick *			joystick;
};

/*************************************************************************************
Input thread argument
*************************************************************************************/
struct input_arg {
	Joystick *			joystick;
};

/*************************************************************************************
Shooter thread argument
*************************************************************************************/
struct shooter_arg {
	DoubleSolenoid *	shooter_piston;
	Talon *				shooter_motor;
};
