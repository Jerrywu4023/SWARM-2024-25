#include "driveFunc.hpp"

// Drive
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

void driveTare() {
	L1.tare_position();
	L2.tare_position();
	L3.tare_position();
	L4.tare_position();
	R1.tare_position();
	R2.tare_position();
	R3.tare_position();
	R4.tare_position();
}

// Intake
void setIntake(int power) {
	intake1.move(power);
	intake2.move(power);
}

void setIntakeSpeed(int speed) {
	intake1.move_velocity(speed);
	intake2.move_velocity(speed);
}

// Lever
void setLever(int power) {
	lever1.move(power);
	lever2.move(power);
}

void setLeverSpeed(int speed) {
	lever1.move_velocity(speed);
	lever2.move_velocity(speed);
}

// Pneumatics
void setTorch(bool state) {
	torch.set_value(!state);
}

void setHeight(bool state) {
	heightAdj.set_value(state);
}

void setDescore(bool state) {
	descore.set_value(state);
}

void setGate(bool state) {
	gate.set_value(state);
}

void setAligner(bool state) {
	aligner.set_value(state);
}