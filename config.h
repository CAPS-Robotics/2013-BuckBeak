 //////////////////////////////////
///////////////////////////////////
/////                         /////
/////       Config File       /////
/////   All defines go here   /////
/////                         /////
///////////////////////////////////
//////////////////////////////////

#ifndef CONFIG_H
#define CONFIG_H
// Possible DEFINES:
// DEBUG: Enables writing smoothing values to the DS
// SUPERDEBUG: Control robot speeds by buttons
// DRIVE: Enable driving
// PNEUMATICS: Enable pneumatics module
// SHOOTER: Enable shooter systems

// PUT 'EM RIGHT HERE
#define DEBUG
#define DRIVE
#define PNEUMATICS
#define SHOOTER

// Motor Ports:
// 1: Front Left Drive Motor
// 2: Front Right Drive Motor
// 3: Back Left Drive Motor
// 4: Back Right Drive Motor
// 6: Shooter Motor Talon
// 7: Shooter Indexing Talon

// Relay Ports:
// 1: Compressor Spike

// Solenoid Ports:
// 1: Left Climbing Forward
// 2: Left Climbing Backwards
// 3: Right Climbing Forward
// 4: Right Climbing Backwards
// 5: Climbing Tilt In
// 6: Climbing Tilt Out
// 8: Shooter Extend
// 7: Shooter Retract

// Digital Ports:
// 14: Digital Pressure Gauge

// Controls:
// (1,2)Left stick: Move and Strafe
// (3)Right stick: rotation
// (1)X: Index for shooter
// (2)A: Strafe mix down
// (3)B: Shooter half power
// (4)Y: Strafe mix up
// (5)LB: Deploy the climber
//     While climbing: Advance to next step
// (7)LT: Climb!
//     While climbing: Kill climb sequence
// (6)RB: Shooter motors while held
// (8)RT: Fire the shooter

// NO TOUCHY TOUCHY
#ifdef SUPERDEBUG
#ifdef DEBUG
#undef DEBUG
#endif

#ifndef DRIVE
#define DRIVE
#endif

#ifdef SHOOTER
#undef SHOOTER
#endif

#ifdef PNEUMATICS
#undef PNEUMATICS
#endif
#endif // SUPERDEBUG

#endif // CONFIG_H
