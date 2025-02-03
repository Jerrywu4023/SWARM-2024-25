#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();

	imu1.reset();
	trackingL.reset_position();
	trackingS.reset_position();
	clamp.set_value(false);
	reacher.set_value(false);

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
		if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L1)) {
			intake1.move_velocity(600);
		} else if (master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) {
			intake1.move(-127);
		} else {
			intake1.move(0);
		}
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