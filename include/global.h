#pragma once

#include "api.h" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp" // IWYU pragma: keep

extern pros::Motor intake;
extern pros::adi::DigitalOut intakeRelease;
extern pros::adi::DigitalOut mogoClamp;
extern pros::adi::DigitalOut basket;
extern pros::adi::DigitalOut sweepArm;
extern pros::Motor arm;
extern pros::adi::DigitalOut trapdoor;
extern pros::Optical intakeStopper;
extern pros::IMU Imu;