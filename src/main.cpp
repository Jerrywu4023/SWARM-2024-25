#include "driveFunc.hpp"

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
	int drivePower;
	int turnPower;
	while (program) {
		drivePower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	turnPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X);

		movePL(drivePower + turnPower);
		movePR(drivePower - turnPower);

		pros::delay(10);
	}
}