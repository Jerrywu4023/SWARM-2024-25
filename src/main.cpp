#include "driverCode.hpp"
#include "autonomous.hpp"

void initialize() {
	pros::lcd::initialize();

	imu1.reset();
	trackingL.reset_position();
	trackingS.reset_position();
	torch.set_value(false);

	pros::lcd::print(1, "a");

	pros::delay(2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	skillsR();
}

void opcontrol() {
	pros::Task odom(odometry);
	bool program = true;
	int autoButton, autoButton2, autoButton3, autoButton4;
	bool autoDrive = false;
	
	while (program) {
		//tankDrive();
		splitArcade();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);

		/*
		if (autoButton && !autoDrive) {
			A_Qual_B();
			endAuto = true;
			autoDrive = true;
		}*/

		pros::delay(10);
	}
}