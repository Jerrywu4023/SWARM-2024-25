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
int sortColourHue = 0;
int colourHue, colourSaturation;
bool controlIntake = true;
bool sortColour = true;

void intakeControl () {
	while (controlIntake) {
		// Get sensor value
		colourHue = colourSort.get_hue();
		colourSaturation = colourSort.get_saturation();

		// Check if need colour sort
		if (sortColour && colourHue > sortColourHue - 20 && colourHue < sortColourHue + 20 && colourSaturation > 0.8) {
			// Is wrong ring, reverse intake
			intake1.move(-50);
			intake2.move(-50);
			pros::delay(300);
		}

		else {
			// Run intake regularly
			intake1.move(intakePower);
			intake2.move(intakePower);
			pros::delay(20);
		}
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
int LBPositions[] = {30, 50, 130, 210};
int LBPos;

void wallStakeControl () {
	while (LBState != -1) {
		LBPos = wallStakePos.get_angle() / 100;

		// Check if wall stake too low
		if (LBPos < LBPositions[LBState] - 3) {
			wallStake1.move(127);
		}

		// Check if wall stake too high
		else if (LBPos > LBPositions[LBState] + 3) {
			wallStake1.move(-127);
		}

		// wall stake posiiton just right
		else {
			wallStake1.move(0);
			wallStake1.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
		}

		pros::delay(10);
	}
}

/**
 * @brief set goal clamp state
 */

void setClamp (bool state) {
	clamp.set_value(state);
}