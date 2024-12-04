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

extern pros::Motor R1;
extern pros::Motor R2;
extern pros::Motor R3;
extern pros::Motor R4;

// Intake Motor
extern pros::Motor intake;

// Pneumatics
extern pros::ADIDigitalOut clamp;

// Sensors
extern pros::IMU imu1;
extern pros::Rotation trackingL;
extern pros::Rotation trackingS;

extern double imu1Multi;

#endif