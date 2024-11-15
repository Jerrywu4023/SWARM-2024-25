#include "driveFunc.hpp"

void initialize() {
	pros::lcd::initialize();
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {
	bool program = true;
	int drivePower;
	int turnPower;
	while (program) {
		drivePower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	turnPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		moveL(drivePower + turnPower);
		moveR(drivePower - turnPower);

		pros::delay(10);
	}
}