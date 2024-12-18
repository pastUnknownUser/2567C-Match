#pragma once

#include "api.h" // IWYU pragma: keep

// Your motors, sensors, etc. should go here.  Below are examples

inline pros::Motor intake(11);
inline pros::adi::DigitalOut intakeRelease('F');
inline pros::adi::DigitalOut sweepArm('G');
inline pros::adi::DigitalOut mogoClamp('H');
inline pros::adi::DigitalOut basket('E');
inline pros::Motor arm(13);
inline pros::adi::DigitalOut trapdoor('A');
inline pros::Optical intakeStopper(17);