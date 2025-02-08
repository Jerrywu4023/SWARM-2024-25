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
	pros::Task LBRun(wallStakeControl);
	
	sortColour = false;

	pros::delay(2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	moveL(50);
	moveR(50);
	pros::delay(2000);

	movePL(0);
	movePR(0);
}

void opcontrol() {
	//pros::Task odom(odometry);
	bool program = true;
	int autoButton, autoButton2, autoButton3, autoButton4;
	bool autoDrive = false;
	
	while (program) {
		tankDrive();
		//splitArcade();

		autoButton = master.get_digital(pros::E_CONTROLLER_DIGITAL_LEFT);
		/*autoButton2 = master.get_digital(pros::E_CONTROLLER_DIGITAL_UP);
		autoButton3 = master.get_digital(pros::E_CONTROLLER_DIGITAL_RIGHT);
		autoButton4 = master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);*/

		if (autoButton && autoDrive) {
			A_Qual_B();
			intakeOn = true;
			endAuto = true;
			autoDrive = true;
		}

		pros::delay(10);
	}
}