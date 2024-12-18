#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();

	imu1.reset();
	trackingL.reset_position();

	pros::delay (2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autoStart(0, 0, 0);
	skills_24();
}

void opcontrol() {
	// pros::Task odom(odometry);

	bool program = true;
	int autoButton;
	
	while (program) {
		
		tankDrive();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

		/*if (autoButton) {
			autoStart(0, 0, 0);
			skills_15();
		}*/

		pros::delay(10);
	}
}