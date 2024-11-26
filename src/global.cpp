#include "main.h" // IWYU pragma: keep
#include "pros/adi.hpp"
#include "pros/imu.hpp"
#include "pros/motors.hpp"
#include "pros/optical.hpp"

pros::Motor intake(11);
pros::adi::DigitalOut intakeRelease('F');
pros::adi::DigitalOut sweepArm('G');
pros::adi::DigitalOut mogoClamp('H');
pros::adi::DigitalOut basket('E');
pros::Motor arm(13);
pros::adi::DigitalOut trapdoor('A');
pros::Optical intakeStopper(17);
pros::IMU Imu(7);