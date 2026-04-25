#include "autoVariables.hpp"
#include "driveFunc.hpp"
#include "driverCode.hpp"
#include "autonomous.hpp"
#include "pros/misc.h"

void initialize() {
	pros::lcd::initialize();

	// Sensor Init
	imu1.reset();
	trackingL.reset_position();
	trackingS.reset_position();
	lever2.tare_position();

	// Pneumatics Init
	setTorch(false);
	setHeight(true);
	setDescore(false);
	setGate(true);

	pros::lcd::print(1, "a");

	pros::delay(2000);
}

void disabled() {}

void competition_initialize() {}

void autonomous() {
	autoStart(0, 0, 0);
	testDrive();
	endAuto = true;
	autoControl = false;
}

void opcontrol() {
	pros::Task odom(odometry);
	bool program = true;
	int autoButton, autoButton2, autoButton3, autoButton4;
	bool autoDrive = false;
	
	while (program) {
		tankDrive();
		//splitArcade();

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