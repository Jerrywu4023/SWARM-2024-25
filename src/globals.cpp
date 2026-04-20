#include "globals.hpp"
#include "pros/imu.hpp"
#include "pros/rotation.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (ordered from front to back)
pros::Motor L1 (16, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L2 (17, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L3 (7, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L4 (10, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
//motor #, port #, gear ratio, fwd/rvrs, encoder units
pros::Motor R1 (18, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R2 (20, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R3 (8, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R4 (9, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
// red - 36:1, green - 18:1 blue - 6:1

// Intake Upper Stage Motor
pros::Motor intake1 (11, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2 (19, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake3 (5, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Pneumatics
pros::ADIDigitalOut torch ('H');

// Sensors
pros::IMU imu1 (3);
pros::Rotation trackingS (2);
pros::Rotation trackingL (4, true);

double imu1Multi = 1;
