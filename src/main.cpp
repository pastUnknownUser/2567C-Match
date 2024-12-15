#include "main.h"
#include "EZ-Template/auton.hpp"
#include "EZ-Template/auton_selector.hpp"
#include "EZ-Template/util.hpp"
#include "autons.hpp"
#include "pros/misc.h"
#include "pros/motors.h"
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// Chassis constructor
ez::Drive chassis(
    // These are your drive motors, the first motor is used for sensing!
    {-16, -18, 17},     // Left Chassis Ports (negative port will reverse it!)
    {20, 9, -15},  // Right Chassis Ports (negative port will reverse it!)

    7,      // IMU Port
    2.75,  // Wheel Diameter (Remember, 4" wheels without screw holes are actually 4.125!)
    600);   // Wheel RPM

/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
  // Print our branding over your terminal :D
  ez::ez_template_print();

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(0);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  chassis.opcontrol_curve_default_set(0, 0);     // Defaults for curve. If using tank, only the first parameter is used. (Comment this line out if you have an SD card!)

  // Set the drive to your own constants from autons.cpp!
  default_constants();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);  // If using tank, only the left side is used.
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
      Auton("red right rush", red_right_rush),
      Auton("red right wp", red_right_win_point),
      Auton("red left wp", red_left_win_point),
      Auton("blue right wp", blue_right_win_point),
      Auton("blue left rush", blue_left_rush),
      Auton("blue left wp", blue_left_win_point),
      Auton("SKILLS", skills),
      Auton("red left four", red_left_four),
      Auton("blue right four", blue_right_four),
    
     
  });

  // Initialize chassis and auton selector
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {
  // . . .
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  chassis.pid_targets_reset();                // Resets PID targets to 0
  chassis.drive_imu_reset();                  // Reset gyro position to 0
  chassis.drive_sensor_reset();               // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);  // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

int clampControl = 1;
int sweepArmControl = 1;
int trapdoorControl = 1;
int basketControl = 1; 
int intakeReleaseControl = 1;

void opcontrol() {
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_COAST;

  chassis.drive_brake_set(driver_preference_brake);

  while (true) {
    chassis.opcontrol_tank();  // Tank control
    // chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade
    // chassis.opcontrol_arcade_standard(ez::SINGLE);  // Standard single arcade
    // chassis.opcontrol_arcade_flipped(ez::SPLIT);    // Flipped split arcade
    // chassis.opcontrol_arcade_flipped(ez::SINGLE);   // Flipped single arcade

    // . . .
    // Put more user control code here!
    // . . .
    // Arm Control
    if (master.get_digital(DIGITAL_L1)) {
      arm.move_voltage(8400); // arm up
      
    } else if (master.get_digital(DIGITAL_L2)) {
      arm.move_voltage(-8400); // arm down
    
    } else {
      arm.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      arm.brake();

    }

    // Intake Control
    if (master.get_digital(DIGITAL_R1)) {
      intake.move_voltage(-12000); // intake in
    } else if (master.get_digital(DIGITAL_R2)) {
      intake.move_voltage(12000); // intake out

    } else {
      intake.move_voltage(0); // intake stop

    }

    // Basket Control
    if (master.get_digital_new_press(DIGITAL_DOWN)) {
      basketControl++; // keeps track if on or off
      if (basketControl % 2 == 0) {
        basket.set_value(true); // sweep arm on
      }
      if (basketControl % 2 == 1) {
        basket.set_value(false); // sweep arm off
      }
    }

    if (master.get_digital_new_press(DIGITAL_RIGHT)) {
      trapdoorControl++; // keeps track if on or off
      if (trapdoorControl % 2 == 0) {
        trapdoor.set_value(true); // sweep arm on
      }
      if (trapdoorControl % 2 == 1) {
        trapdoor.set_value(false); // sweep arm off
      }
    }

    // Clamp Control
    if (master.get_digital_new_press(DIGITAL_B)) {
      clampControl++; // keeps track if on or off
      if (clampControl % 2 == 0) {
        mogoClamp.set_value(false); // mogo clamp on
      }
      if (clampControl % 2 == 1) {
        mogoClamp.set_value(true); // mogo clamp off
      }
    }

    // Sweep Arm Control
    if (master.get_digital_new_press(DIGITAL_Y)) {
      sweepArmControl++; // keeps track if on or off
      if (sweepArmControl % 2 == 0) {
        sweepArm.set_value(true); // sweep arm on
      }
      if (sweepArmControl % 2 == 1) {
        sweepArm.set_value(false); // sweep arm off
      }
    }

    if (master.get_digital_new_press(DIGITAL_A)) {
      intakeReleaseControl++;
      if (intakeReleaseControl % 2 == 0) {
        intakeRelease.set_value(true);
      }
      if (intakeReleaseControl % 2 == 1) {
        intakeRelease.set_value(false);
      }
    }
    

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}