#include "globals.hpp"
#include "pros/rotation.h"

// Controller
pros::Controller master(pros::E_CONTROLLER_MASTER);

// Drive Motors (ordered from front to back)
pros::Motor L1 (1, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L2 (2, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L3 (3, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor L4 (4, pros::E_MOTOR_GEARSET_06, 0, pros::E_MOTOR_ENCODER_DEGREES);

pros::Motor R1 (5, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R2 (6, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R3 (7, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
pros::Motor R4 (8, pros::E_MOTOR_GEARSET_06, 1, pros::E_MOTOR_ENCODER_DEGREES);
