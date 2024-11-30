#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	testDrive();
}

void opcontrol() {
	bool program = true;
	int autoButton;
	
	while (program) {
		
		tankDrive();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
		if (autoButton) 
			testDrive();

		pros::delay(10);
	}
}