#include "globals.hpp"
#include "pros/imu.hpp"
#include "pros/motors.h"
#include "pros/rotation.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (ordered from front to back)
pros::Motor L1 (13, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L2 (14, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L3 (15, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L4 (16, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
//motor #, port #, gear ratio, fwd/rvrs, encoder units
pros::Motor R1 (17, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R2 (18, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R3 (19, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R4 (20, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);

// Intake
pros::Motor intake1 (12, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor intake2 (11, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);

// Lever
pros::Motor lever1 (10, pros::E_MOTOR_GEARSET_36, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor lever2 (9, pros::E_MOTOR_GEARSET_36, 1, pros::E_MOTOR_ENCODER_DEGREES);

// Pneumatics
pros::ADIDigitalOut torch ('E');
pros::ADIDigitalOut heightAdj ('C');
pros::ADIDigitalOut descore ('B');
pros::ADIDigitalOut gate ('A');
pros::ADIDigitalOut aligner ('D');

// Sensors
pros::IMU imu1 (1);
pros::Rotation trackingS (5);
pros::Rotation trackingL (6, true);

double imu1Multi = 1.0087;
