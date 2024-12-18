#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();

	imu1.reset();
	trackingL.reset_position();
	trackingS.reset_position();
	clamp.set_value(true);

	pros::delay (2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autoStart(0, 0, 0);
	skills_15();
}

void opcontrol() {
	bool program = true;
	int autoButton;
	bool autoDrive = false;
	
	while (program) {
		
		tankDrive();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

		if (autoButton && !autoDrive) {
			autoStart(0, 0, 0);
			driverSkills();
			intakeOn = true;
			endAuto = true;
			autoDrive = true;
		}

		pros::delay(10);
	}
}