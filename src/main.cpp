#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	test();
}

void opcontrol() {
	bool program = true;
	
	while (program) {
		
		tankDrive();

		pros::delay(10);
	}
}