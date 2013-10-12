/*************************************************************************************
* Robit.cpp
*
* Defines the main robot class, as well as the thread functions
*************************************************************************************/

/*************************************************************************************
Includes
*************************************************************************************/
#include "Robit.h"

#include "pthread.h"
#include "semaphore.h"
#include "time.h"
#include "unistd.h"
#include "WPILib.h"

/*************************************************************************************
Global variables
*************************************************************************************/
sem_t shooter_semaphore;

/*************************************************************************************
Robot class constructor
*************************************************************************************/
myRobit::myRobit(){
    // Set up the shooter's semaphore
    sem_init( &shooter_semaphore, 0, 0 );
}

/*************************************************************************************
Robot class destructor
*************************************************************************************/
myRobit::~myRobit(){}

/*************************************************************************************
RobotInit
 - Runs after all OS setup
*************************************************************************************/
void myRobit::RobotInit(){
    // Set up the control objects
    compressor =            new Compressor( PRESSURE_SWITCH, COMPRESSOR_PORT );
    drivetrain =            new RobotDrive( FRONT_LEFT_MOTOR, BACK_LEFT_MOTOR, FRONT_RIGHT_MOTOR, BACK_RIGHT_MOTOR );
    joystick =              new Joystick( JOYSTICK_PORT );
    shooter_motor =         new Talon( TALON_PORT );
    shooter_piston =        new DoubleSolenoid( SHOOTER_PISTON_FORE, SHOOTER_PISTON_BACK );

    // Set all starting values for objects
    compressor->Start();
    shooter_piston->Set( shooter_piston->kReverse );

    // Set up thread argument structs
    struct drive_arg driveArgStruct = { drivetrain, joystick };
    struct input_arg inputArgStruct = { joystick };
    struct shooter_arg shooterArgStruct = { shooter_piston, shooter_motor };

    // Start all the threads
    pthread_create( &driveThread, NULL, driveFunc, (void *) &driveArgStruct );
    pthread_create( &inputThread, NULL, inputFunc, (void *) &inputArgStruct );
    pthread_create( &shooterThread, NULL, shooterFunc, (void *) &shooterArgStruct );
}

/*************************************************************************************
AutonomousInit
 - Runs once at start of autonomous period
*************************************************************************************/
void myRobit::AutonomousInit(){
    int                     i;              /* Counter variable                     */
    
    // Fire four times
    for( i = 0; i < 4; ++i ){
        sem_post( &shooter_semaphore );
    }
}

/*************************************************************************************
DriveFunc
 - Drives the robot asynchronously
*************************************************************************************/
void * driveFunc( void * arg ){
    struct drive_arg * driveArg = (struct drive_arg *) arg;
                                            /* Cast argument                        */

    while ( 1 ){
        // Do dat drive thang
        driveArg->drivetrain->MecanumDrive_Cartesian(
            driveArg->joystick->GetRawAxis( AXIS_LEFT_X ),
            driveArg->joystick->GetRawAxis( AXIS_LEFT_Y ), 
            driveArg->joystick->GetRawAxis( AXIS_RIGHT_X ) );
    }
}

/*************************************************************************************
InputFunc
 - If the shoot button is pushed, post to the shooters semaphore
*************************************************************************************/
void * inputFunc( void * arg ){
    struct input_arg * inputArg = (struct input_arg *) arg;
                                            /* Cast argument                        */
    struct timespec waitstruct = { 0, 200000000 };
                                            /* Set up wait structure                */

    while ( 1 ){
        // Post the semaphore if button push, debounce for 200 ms
        if( inputArg->joystick->GetRawButton( BTN_A ) ){
            sem_post( &shooter_semaphore );
            nanosleep( &waitstruct, NULL );
        }
    }
}

/*************************************************************************************
shooterFunc
 - Waits on the semaphore, then fires
*************************************************************************************/
void * shooterFunc( void * arg ){
    struct shooter_arg * shooterArg = (struct shooter_arg *) arg;
                                            /* Cast argument                        */
    struct timespec waitstruct = { 0, 500000000 };
                                            /* Set up wait structure                */
    int val;                                /* Used for checking semaphore value    */
    
    while( 1 ){
        // Wait for the semaphore
        sem_wait( &shooter_semaphore );

        // Start the shooter motor
        shooterArg->shooter_motor->Set( 1.0 );
        sleep( 1 );

        // Pulse the firing piston
        shooterArg->shooter_piston->Set( shooterArg->shooter_piston->kForward );
        nanosleep( &waitstruct, NULL );
        shooterArg->shooter_piston->Set( shooterArg->shooter_piston->kReverse );

        // Only stop the motor if we aren't firing again
        sem_getvalue( &shooter_semaphore, &val );
        if( !val ){
            shooterArg->shooter_motor->Set( 0.0 );
        }
    }
}

// Cruddy FIRST start macro function
START_ROBOT_CLASS( myRobit );
