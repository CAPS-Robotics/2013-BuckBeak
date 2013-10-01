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
// AUTOMODE: Enable autonomous program
// COMPRESSOR: Enable compressor, included by SHOOTER and PNEUMATICS
// TESTING: Enable testing module

// PUT 'EM RIGHT HERE
#define DEBUG
#define DRIVE
#define PNEUMATICS
#define SHOOTER
#define COMPRESSOR
#define AUTOMODE

// Motor Ports:
// 1: Front Left Drive Motor
// 2: Front Right Drive Motor
// 3: Back Left Drive Motor
// 4: Back Right Drive Motor
// 6: Shooter Motor Talon
// 7: Shooter Indexing Talon

// Relay Ports:
// 3: Compressor Spike

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
// 13: Digital Pressure Gauge

// Controls:
// (1,2)Left stick: Move and Strafe
// (3)Right stick: rotation
// (1)X: Index for shooter
// (2)A: Strafe mix down
// (4)Y: Strafe mix up
// (5)LB: Deploy Climber
// (7)LT: Direct set value to climber
// (6)RB: Manual Load Shooter
// (8)RT: Manual Fire Shooter

#ifdef PNEUMATICS
#ifndef COMPRESSOR
#define COMPRESSOR
#endif
#endif

#ifdef SHOOTER
#ifndef COMPRESSOR
#define COMPRESSOR
#endif
#endif

// NO TOUCHY TOUCHY
#ifdef SUPERDEBUG
#ifndef DEBUG
#define DEBUG
#endif

#ifndef DRIVE
#define DRIVE
#endif

#ifndef SHOOTER
#define SHOOTER
#endif

#ifdef PNEUMATICS
#undef PNEUMATICS
#endif

#ifdef COMPRESSOR
#undef COMPRESSOR
#endif
#endif // SUPERDEBUG

#ifdef TESTING
#ifdef SUPERDEBUG
#undef SUPERDEBUG
#endif

#ifdef DEBUG
#undef DEBUG
#endif

#ifdef DRIVE
#undef DRIVE
#endif

#ifdef SHOOTER
#undef SHOOTER
#endif

#ifdef PNEUMATICS
#undef PNEUMATICS
#endif

#ifdef COMPRESSOR
#undef COMPRESSOR
#endif
#endif // TESTING

#endif // CONFIG_H
