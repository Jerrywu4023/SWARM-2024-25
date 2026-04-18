#ifndef _DRIVE_
#define _DRIVE_

#include "globals.hpp"

// Drive
void moveL(int velocity);

void moveR(int velocity);

void movePL(int power);

void movePR(int power);

void HardBreak();

void driveTare();

// Intake
void setIntake(int power);

void setIntakeSpeed(int power);

// Lever
void setLever(int power);

void setLeverSpeed(int speed);

// Pneumatics
void setTorch(bool state);

void setHeight(bool state);

void setDescore(bool state);

void setGate(bool state);

void setAligner(bool state);

#endif