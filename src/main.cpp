#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();

	imu1.reset();
	trackingL.reset_position();
	trackingS.reset_position();
	clamp.set_value(false);
	reacher.set_value(false);

	pros::Task intakeRun(intakeControl);
	

	pros::delay(2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	skills_15();
}

void opcontrol() {
	//pros::Task odom(odometry);
	bool program = true;
	int autoButton;
	bool autoDrive = false;
	
	while (program) {
		splitArcade();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);

		if (autoButton && !autoDrive) {
			A_Qual_B();
			intakeOn = true;
			endAuto = true;
			autoDrive = true;
		}

		pros::delay(10);
	}
}