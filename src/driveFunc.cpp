#include "driveFunc.hpp"

void moveL(int velocity) {
	L1.move_velocity(velocity);
	L2.move_velocity(velocity);
	L3.move_velocity(velocity);
	L4.move_velocity(velocity);
}

void moveR(int velocity) {
    R1.move_velocity(velocity);
	R2.move_velocity(velocity);
	R3.move_velocity(velocity);
	R4.move_velocity(velocity);
}

void movePL(int power) {
	L1.move(power);
	L2.move(power);
	L3.move(power);
	L4.move(power);
}

void movePR(int power) {
	R1.move(power);
	R2.move(power);
	R3.move(power);
	R4.move(power);
}

void HardBreak() {
	moveL(0);
	moveR(0);
	L1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	L2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	L3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	L4.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	R1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	R2.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	R3.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
	R4.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
}

void driveTare () {
	L1.tare_position();
	L2.tare_position();
	L3.tare_position();
	L4.tare_position();
	R1.tare_position();
	R2.tare_position();
	R3.tare_position();
	R4.tare_position();
}

int getAvgCurrent () {
	int totalCurrent = L1.get_current_draw() + L2.get_current_draw() + L3.get_current_draw()
						+ L4.get_current_draw() + R1.get_current_draw() + R2.get_current_draw()
						+ R3.get_current_draw() + R4.get_current_draw();
	return totalCurrent / 8;
}

/**
 * @brief Powers the intake with colour sorting
 */
const int redAlliance = 215;
const int blueAlliance = 12;

int intakePower = 0;
int sortColourHue = 12;
int colourHue;
double colourSaturation;
bool controlIntake = true;
bool sortColour = true;

bool checkColour () {
	for (int i = 0; i < 5; i++) {
		if (!(sortColour && colourHue > sortColourHue - 20 && colourHue < sortColourHue + 20 && colourSaturation > 0.3)) 
			return false;
		pros::delay(50);
	}
	return true;
}

bool checkStall () {
	for (int i = 0; i < 5; i++) {
		if (!(abs(intake1.get_actual_velocity() + intake2.get_actual_velocity()) < 20 && intakePower != 0 && LBState != 1)) 
			return false;
		pros::delay(50);
	}
	return true;
}

void intakeControl () {
	colourSort.set_led_pwm(100);
	while (controlIntake) {
		// Get sensor value
		colourHue = colourSort.get_hue();
		colourSaturation = colourSort.get_saturation();
		pros::lcd::print(2, "hue: %d", colourHue);
		pros::lcd::print(3, "sat: %d", colourSaturation);

		// Run intake regularly
		intake1.move(intakePower);
		intake2.move(intakePower);
		intakeFront.move(intakePower);
		pros::delay(20);

		// Check if need colour sort
		/*if (sortColour && colourHue > sortColourHue - 20 && colourHue < sortColourHue + 20 && colourSaturation > 0.4) {
			if (checkColour()) {
				// Is wrong ring, reverse intake
				intake1.move(-50);
				intake2.move(-50);
				pros::delay(200);
			}
		}

		else if (abs(intake1.get_actual_velocity() + intake2.get_actual_velocity()) < 20 && intakePower != 0 && LBState != 1) {
			intake1.move(intakePower);
			intake2.move(intakePower);
			pros::delay(200);
			if (checkStall()) {
				intake1.move(-127);
				intake2.move(-127);
				pros::delay(300);
			}
		}*/

	}
}

void setIntake (int power) {
	intakePower = power;
}

/**
 * @brief Wall stake mech control
 * 
 * States: 0 - rest, 1 - load ring, 2 - up, 3 - score down
 */

int LBState = 0;
int LBPositions[] = {0, 30, 120, 160};
double LBPos, LBPosDiff;

void wallStakeControl () {
	while (LBState != -1) {
		LBPos = 360 - (wallStakePos.get_angle() / 100);
		if(LBPos > 270) LBPos -= 360;
		pros::lcd::print(0, "LBPos: %f", LBPos);
		// Find difference between current pos and desired pos
		LBPosDiff = LBPositions[LBState] - LBPos;

		// Move arm based on difference in position
		wallStake1.move(LBPosDiff * 1.5);
		wallStake2.move(LBPosDiff * 1.5);

		pros::delay(10);
	}
}

/**
 * @brief set goal clamp state
 */

void setClamp (bool state) {
	clamp.set_value(state);
}

/**
 * @brief set reacher state
 */

void setReacher (bool state) {
	reacher.set_value(state);
}