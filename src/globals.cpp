#include "globals.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (ordered from front to back)
pros::Motor L1 (5, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L2 (4, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L3 (2, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L4 (3, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
//motor #, port #, gear ratio, fwd/rvrs, encoder units
pros::Motor R1 (19, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R2 (16, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R3 (20, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R4 (15, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
// red - 36:1, green - 18:1 blue - 6:1

// Intake Motor
pros::Motor intake1 (13, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2 (10, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);

// Wall Stake Motor
pros::Motor wallStake1 (10, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Pneumatics
pros::ADIDigitalOut clamp ('H');
pros::ADIDigitalOut reacher ('A');

// Sensors
pros::IMU imu1 (12);
pros::Rotation trackingS (1);
pros::Rotation trackingL (11);

pros::Rotation wallStakePos (9);

pros::Optical colourSort (18, 20);

double imu1Multi = 1.007;
