#ifndef _GLOBALS_
#define _GLOBALS_

#include "main.h"

// Controller
extern pros::Controller master;

// Drive Motors (ordered from front to back)
extern pros::Motor L1;
extern pros::Motor L2;
extern pros::Motor L3;
extern pros::Motor L4;
extern pros::Motor L5;

extern pros::Motor R1;
extern pros::Motor R2;
extern pros::Motor R3;
extern pros::Motor R4;
extern pros::Motor R5;

// Pneumatics
extern pros::ADIDigitalOut PTO;

// Sensors
extern pros::IMU imu1;
extern pros::Rotation trackingL;
extern pros::Rotation climbTrack;

extern double imu1Multi;

#endif