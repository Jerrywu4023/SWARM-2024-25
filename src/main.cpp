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
	int leftPower;
	int rightPower;
	int intakeButton;
	while (program) {
		leftPower = master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y);
    	rightPower = master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_Y);
		intakeButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);

		movePL(leftPower);
		movePR(rightPower);

		if (intakeButton)
			intake.move(127);
		else
			intake.move(0);

		pros::delay(10);
	}
}