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
extern pros::Motor intake1;
extern pros::Motor intake2;

// Wall Stake Motor
extern pros::Motor wallStake1;

// Pneumatics
extern pros::ADIDigitalOut clamp;
extern pros::ADIDigitalOut reacher;

// Sensors
extern pros::IMU imu1;
extern pros::Rotation trackingL;
extern pros::Rotation trackingS;

extern pros::Rotation wallStakePos;

extern pros::Optical colourSort;

extern double imu1Multi;

#endif