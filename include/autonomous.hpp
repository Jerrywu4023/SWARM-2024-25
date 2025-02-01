#ifndef _AUTO_
#define _AUTO_

#include "drivefunc.hpp"
#include "autocontrol.hpp"
#include "odometry.hpp"

// Auto Setup
void autoStart (int x, int y, int heading, int* hue);

// Test Code
void testDrive ();

void testTurn ();

// Qualification Autos
void A_Qual_R ();

void A_Qual_B ();

//Elimination Autos
void A_Elim_R_In ();

void A_Elim_R_Out ();

void A_Elim_B_In ();

void A_Elim_R_Out ();

// Skills
void skills_15 ();

void driverSkills ();

#endif