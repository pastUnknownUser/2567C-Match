#include "autons.hpp"
#include "liblvgl/core/lv_obj_class.h" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

void FWD(float distance, int speed) {
  chassis.pid_drive_set(distance, speed, true);
  chassis.pid_wait();
}
void REV(float distance, int speed) {
  chassis.pid_drive_set(-distance, speed, true);
  chassis.pid_wait();
}
void turn(float heading, int speed) {
  chassis.pid_turn_set(heading, speed, false);
  chassis.pid_wait();
}


void ColorSensor() {
  intakeStopper.set_led_pwm(100);
  if (intakeStopper.get_hue() < 15) { //Blue Rings
    intake.move_voltage(0);
  } else if (intakeStopper.get_hue() > 200) { // Red Rings
    intake.move_voltage(0);
  }
}

// These are out of 127
const int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 90;

///
// Constants
///
void default_constants() {
  chassis.pid_heading_constants_set(11, 0, 20);
  chassis.pid_drive_constants_set(11, 0, 100);
  chassis.pid_turn_constants_set(3, 0.05, 20, 15);
  chassis.pid_swing_constants_set(6, 0, 65);

  chassis.pid_turn_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);
}

void red_right_rush() {
  //line up with line of tabs, brake calling me
  arm.move_relative(500, 100);
  REV(32.5, 70);
  turn(-29.2, 49);
  REV(17, 49);
  mogoClamp.set_value(true);
  pros::delay(100);
  turn(10, 49);
  intake.move_voltage(-12000);
  pros::delay(500);
  FWD(18, 70);
  REV(10, 70);
  pros::delay(1000);
  mogoClamp.set_value(false);
  FWD(9.5, 70);
  turn(-90, 49);  
  REV(15.5, 70);
  mogoClamp.set_value(true);
  pros::delay(100);
  turn(47, 49);
}

void red_right_win_point() {
  
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(11, 90);
  arm.move_relative(-500, 100);
  pros::delay(500);
  REV(37, 90);
  arm.move_relative(-440, 100);
  mogoClamp.set_value(true);
  turn(-125, 100);
  intake.move_voltage(-12000);
  FWD(24.5, 90);
  arm.move_relative(500, 100);
  turn(36, 100);
  intakeRelease.set_value(true);
  FWD(44,90 );
  intakeRelease.set_value(false);
  REV(20, 90);
  turn(95, 100);
  FWD(11, 90);

}

void red_left_win_point() {
  //pros::Task heading(live_heading);

  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(11.5, 100);
  arm.move_relative(-500, 100);
  pros::delay(500);
  REV(37, 65);
  mogoClamp.set_value(true);
  turn(125, 100);
  intake.move_voltage(-12000);
  FWD(23, 100);
  turn(212, 100);
  FWD(15.5, 100);
  pros::delay( 500);
  REV(15.5, 100);
  turn(191, 100);
  FWD(16.5, 100);
  pros::delay( 500);
  REV(16.5, 100);
  intakeRelease.set_value(true);
  turn(323, 100);
  FWD(44, 100);
  pros::delay(500);
  intakeRelease.set_value(false);
  REV(10, 100);
  pros::delay(500);
  turn(245, 100);
  FWD(19, 100);

}

void blue_right_win_point() {
  
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(11.5, 100);
  arm.move_relative(-500, 100);
  pros::delay(500);
  REV(37, 65);
  mogoClamp.set_value(true);
  turn(-125, 100);
  intake.move_voltage(-12000);
  FWD(23, 100);
  turn(-212, 100);
  FWD(15.5, 100);
  pros::delay( 500);
  REV(15.5, 100);
  turn(-191, 100);
  FWD(16.5, 100);
  pros::delay( 500);
  REV(16.5, 100);
  intakeRelease.set_value(true);
  turn(-323, 100);
  FWD(44, 100);
  pros::delay(500);
  intakeRelease.set_value(false);
  REV(10, 100);
  pros::delay(500);
  turn(-245, 100);
  FWD(19, 100);
  
}

void blue_left_win_point() {

  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(11, 90);
  arm.move_relative(-500, 100);
  pros::delay(500);
  REV(37, 90);
  arm.move_relative(-440, 100);
  mogoClamp.set_value(true);
  turn(125, 100);
  intake.move_voltage(-12000);
  FWD(24.5, 90);
  arm.move_relative(500, 100);
  turn(-36, 100);
  intakeRelease.set_value(true);
  FWD(44, 90);
  intakeRelease.set_value(false);
  REV(20, 90);
  turn(-95, 100);
  FWD(11, 90);

}

void skills() {
  //alliance stake
  basket.set_value(true);
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  pros::delay(1000);
  FWD(10, 100);
  arm.move_relative(-500, 100);
  pros::delay(100);
  REV(9, 100);
  //1st goal
  turn(80, 100);
  REV(18, 80);
  mogoClamp.set_value(true);
  turn(195, 100);
  intake.move_voltage(-12000);
  FWD(22, 75);
  turn(230, 100);
  FWD(42, 75);
  turn(20, 100);
  FWD(24, 75);
  turn(0, 100);
  FWD(23, 75);
  pros::delay(300);
  FWD(8, 75);
  pros::delay(700);
  REV(15, 75);
  turn(-62, 100);
  pros::delay(300);
  FWD(11, 75);
  REV(12, 100);
  turn(138, 100);
  REV(17, 100);
  mogoClamp.set_value(false);
  FWD(6, 75);
  REV(10, 100);
  FWD(10, 75);
  //2nd goal
  turn(268, 100);
  REV(73,70);
  mogoClamp.set_value(true);
  basket.set_value(false);
  turn(166, 100);
  FWD(22, 75);
  turn(122, 100);
  FWD(42, 75);
  turn(-15, 100);
  FWD(24.5, 75);
  turn(0, 100);
  FWD(28, 75);
  pros::delay(300);
  FWD(14.5, 75);
  pros::delay(300);
  REV(18, 80);
  turn(55, 100);
  pros::delay(300);
  FWD(13, 75);
  pros::delay(100);
  REV(13, 75);
  turn(-145, 100);
  REV(20, 100);
  mogoClamp.set_value(false);
  pros::delay(100);
  intake.move_voltage(12000);
  FWD(8, 100);
  REV(15, 100);
  FWD(15, 100);
  //3rd goal
  turn(-165, 100);
  FWD(88, 100);
  basket.set_value(true);
  turn(-140, 100);
  FWD(33, 100);
  turn(-251, 100);
  FWD(60, 100);
  REV(15, 100);
  FWD(20, 100);
  REV(20, 100);
  //4th goal
  turn( -90, 100);
  FWD(50, 100);
  turn(-115, 100);
  FWD(70, 100);
  REV(25, 100);
  //hang
  turn(34, 100);
  basket.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 100);
  sweepArm.set_value(true);
  FWD(55, 100);
  REV(10, 100);
//this code sucks and i hate this i just want to rebuild and qualify for worlds 

}

///
// Combining Turn + Drive
///
void test() {
  chassis.pid_drive_set(24_in, 100, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0, TURN_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, 100, true);
  chassis.pid_wait();

}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}

// . . .
// Make your own autonomous functions here!
// . . .