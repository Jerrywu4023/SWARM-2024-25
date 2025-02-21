#include "globals.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (ordered from front to back)
pros::Motor L1 (18, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L2 (19, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L3 (17, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L4 (13, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
//motor #, port #, gear ratio, fwd/rvrs, encoder units
pros::Motor R1 (20, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R2 (16, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R3 (14, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R4 (12, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
// red - 36:1, green - 18:1 blue - 6:1

// Intake Motor
pros::Motor intake1 (7, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2 (9, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intakeFront (1, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Wall Stake Motor
pros::Motor wallStake1 (6, pros::E_MOTOR_GEARSET_36, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor wallStake2 (3, pros::E_MOTOR_GEARSET_36, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Pneumatics
pros::ADIDigitalOut clamp ('A');
pros::ADIDigitalOut reacher ('B');

// Sensors
pros::IMU imu1 (15);
pros::Rotation trackingS (10);
pros::Rotation trackingL (8);

pros::Rotation wallStakePos (4);

pros::Optical colourSort (2, 20);

double imu1Multi = 1.00;
