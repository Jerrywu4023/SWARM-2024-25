#include "driverCode.hpp"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	moveL(50);
	moveR(50);
	pros::delay(700);
	moveL(0);
	moveR(0);
}

void opcontrol() {
	bool program = true;
	
	while (program) {
		
		tankDrive();

		pros::delay(10);
	}
}