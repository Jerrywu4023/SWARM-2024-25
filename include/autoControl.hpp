#ifndef _AUTOCTRL_
#define _AUTOCTRL_

#include "autoVariables.hpp"
#include "driveFunc.hpp"

void setPos (double x, double y, bool restrict);

void setHeading (double heading);

void vectorCalculation ();

void driveControl ();

void turnControl ();

void powerOutput ();

#endif