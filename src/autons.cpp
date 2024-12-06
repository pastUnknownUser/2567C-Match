#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

void FWD(float distance, int speed) {
  chassis.pid_drive_set(distance, speed, true);
  chassis.pid_wait();
  pros::delay(75);
}
void REV(float distance, int speed) {
  chassis.pid_drive_set(-distance, speed, true);
  chassis.pid_wait();
  pros::delay(75);
}
void turn(float heading, int speed) {
  chassis.pid_turn_set(heading, speed, true);
  chassis.pid_wait();
  pros::delay(75);
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

void red_right_win_point() {
  //pros::Task heading(live_heading);

  arm.move_relative(360, 100);
  basket.set_value(true);
  REV(20, 100);
  mogoClamp.set_value(true);
  pros::delay(100);
  FWD(5, 127);
  REV(5, 127);
  turn(-40 ,100);
  intake.move_voltage(-12000);
  
  FWD(22, 100);

  /*
  intakeRelease.set_value(false);
  pros::delay(300);
  REV(22, 100);
  turn(180, 100);
  mogoClamp.set_value(false);
  REV(5, 127);
  FWD(5, 127);
  pros::delay(250);
  turn(75, 100);
  REV(28, 100);
  mogoClamp.set_value(false);
  pros::delay(100);
  turn(-5, 100);
  FWD(12.5, 100);
  turn(95, 100);
  FWD(45, 100);
  */

}

void blue_right_win_point() {
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(720, 100);
  pros::delay(100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(9, 100);
  arm.move_relative(-300, 100);
  pros::delay(500);
  REV(9, 100);
  turn(-25,100);
  REV(8, 100);
  turn(-35, 100);
  REV(27, 100);
  mogoClamp.set_value(true);
  turn(-165, 100);
  intake.move_voltage(-12000);
  turn(-150, 100);
  FWD(28, 100);
  REV(3, 100);
  turn(-240, 100);
  FWD(14, 100);
  REV(14, 100);
  turn(-218, 100);
  FWD(15, 100);
  REV(14, 100);
  turn(45, 100);
  arm.move_relative(800, 100);
  FWD(40, 100);
  


}

void red_left_win_point() {
  //pros::Task heading(live_heading);

  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(720, 100);
  pros::delay(100);
  basket.set_value(true);
  pros::delay(1000);
  FWD(9, 100);
  arm.move_relative(-300, 100);
  pros::delay(500);
  REV(9, 100);
  turn(25,100);
  REV(8, 100);
  turn(35, 100);
  REV(27, 100);
  mogoClamp.set_value(true);
  turn(165, 100);
  intake.move_voltage(-12000);
  turn(150, 100);
  FWD(28, 100);
  REV(3, 100);
  turn(240, 100);
  FWD(14, 100);
  REV(14, 100);
  turn(218, 100);
  FWD(15, 100);
  REV(14, 100);
  turn(-45, 100);
  arm.move_relative(800, 100);
  FWD(40, 100);
  

}

void blue_left_win_point() {
  /*
  //scoring alliance
  pros::delay(500);
  arm.move_relative(650, 100);
  pros::delay(500);
  basket.set_value(true);
  pros::delay(500);
  chassis.pid_drive_set(12_in, 50, true);
  chassis.pid_wait();
  arm.move_relative(-350, 100);
  chassis.pid_drive_set(-8_in, 50, true);
  chassis.pid_wait();
  basket.set_value(false);
  chassis.pid_turn_set(-20, 70, true);
  chassis.pid_wait();
  //clamping mogo goal
  chassis.pid_drive_set(-26_in, 50, true);
  chassis.pid_wait();
  mogoClamp.set_value(true);
  pros::delay(250);
 */
  arm.move_relative(360, 100);
  basket.set_value(true);
  REV(20, 100);
  mogoClamp.set_value(true);
  pros::delay(100);
  FWD(5, 127);
  REV(5, 127);
  turn(-87.5, 100);
  intake.move_voltage(-12000);
  intakeRelease.set_value(true);
  FWD(22, 100);
  intakeRelease.set_value(false);
  pros::delay(300);
  REV(-22, 100);
  turn(180, 100);
  mogoClamp.set_value(false);
  REV(5, 127);
  FWD(5, 127);
  pros::delay(250);
  turn(-75, 100);
  REV(28, 100);
  mogoClamp.set_value(false);
  pros::delay(100);
  turn(5, 100);
  FWD(12.5, 100);
  turn(-95, 100);
  FWD(45, 100);
}

void skills() {
  //pros::Task heading(live_heading);

  arm.move_relative(360, 100);
  chassis.pid_drive_set(-6_in, 100, true);
  chassis.pid_wait();
  mogoClamp.set_value(true); //1st mogo
  pros::delay(500);
  chassis.pid_drive_set(1_in, 100, false);
  chassis.pid_wait();
  chassis.pid_drive_set(-1_in, 100, false);
  chassis.pid_wait();
  intake.move_velocity(-12000);
  pros::delay(750);
  chassis.pid_turn_set(155, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(24_in, 100, true); //1st ring
  chassis.pid_wait();
  chassis.pid_turn_set(215, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(22.5_in,  65,true); //2nd ring
  chassis.pid_wait();
  chassis.pid_turn_set(308, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(18_in, 100, true); //3rd ring
  chassis.pid_wait();
  chassis.pid_turn_set(262, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(9_in,100, true); //4th ring
  chassis.pid_wait();
  chassis.pid_turn_set(336, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(16_in, 100, true); //5th ring
  chassis.pid_wait();
  chassis.pid_drive_set(-20_in, 100, true);
  chassis.pid_wait();
  chassis.pid_turn_set(128, 80, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-22_in, 100, true);
  chassis.pid_wait();
  mogoClamp.set_value(false); //mogo corner
  pros::delay(500);
  chassis.pid_drive_set(15_in ,100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-15_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(12_in, 100, false);
  chassis.pid_wait();
  chassis.pid_turn_set(235.45, 50, true); //drive across
  chassis.pid_wait();
  
  chassis.pid_drive_set(-77, 85, true);
  chassis.pid_wait();
  mogoClamp.set_value(true); //2nd mogo
  pros::delay(100);
  chassis.pid_turn_set(146, 70, true);
  chassis.pid_wait();
  chassis.pid_drive_set(21_in, 100, true); //1st ring
  chassis.pid_wait();
  chassis.pid_turn_set(63, 80, true);
  chassis.pid_wait();
  arm.move_relative(-50, 100);
  pros::delay(150);
  chassis.pid_drive_set(28_in, 80, true);
  chassis.pid_wait();
  chassis.pid_turn_set(335, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(20_in, 100, true);
  chassis.pid_wait();
  pros::delay(500);
  chassis.pid_drive_set(13_in, 100, true);
  chassis.pid_wait();
  chassis.pid_turn_set(60, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 100, true);
  chassis.pid_wait();
  chassis.pid_turn_set(176, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-21_in, 100, true);
  chassis.pid_wait();
  mogoClamp.set_value(false);
  pros::delay(100);
  chassis.pid_drive_set(13_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-13_in, 100, true);
  chassis.pid_wait();
  chassis.pid_drive_set(13_in, 100, true);
  chassis.pid_wait();
  
  
}

void skills2() {
  //pros::Task heading(live_heading);
  /*
  basket.set_value(true);
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  pros::delay(1000);
  chassis.pid_drive_set(8.7, 70, true);
  chassis.pid_wait();
  arm.move_relative(-500, 100);
  pros::delay(500);
  chassis.pid_drive_set(-9, 70, true);
  chassis.pid_wait();
  arm.move_relative(-470, 100);
  chassis.pid_turn_set(80_deg, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-18, 70, true);
  chassis.pid_wait();
  mogoClamp.set_value(true);
  chassis.pid_turn_set(195_deg, 49, true);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  chassis.pid_drive_set(22, 70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(230_deg, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-42, 70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(35_deg, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(25, 70, true);
  chassis.pid_wait();
  */

  basket.set_value(true);
  trapdoor.set_value(true);
  pros::delay(100);
  arm.move_relative(770, 100);
  pros::delay(1000);
  chassis.pid_drive_set(8.7, 70, true);
  chassis.pid_wait();
  arm.move_relative(-500, 100);
  pros::delay(500);
  chassis.pid_drive_set(-9, 70, true);
  chassis.pid_wait();
  arm.move_relative(-470, 100);
  chassis.pid_turn_set(80, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(-18, 70, true);
  chassis.pid_wait();
  mogoClamp.set_value(true);
  chassis.pid_turn_set(195, 49, true);
  chassis.pid_wait();
  intake.move_voltage(-12000);
  chassis.pid_drive_set(22,70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(230, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(42, 70, true);
  chassis.pid_wait();
  chassis.pid_turn_set(20, 49, true);
  chassis.pid_wait();
  chassis.pid_drive_set(25, 70, true);
  chassis.pid_wait();
  

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