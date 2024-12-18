#include "autons.hpp"
#include "global.h"
#include "liblvgl/core/lv_obj_class.h" // IWYU pragma: keep
#include "main.h" // IWYU pragma: keep
#include "pros/rtos.hpp"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

void Forward(float distance, int speed) {
  chassis.pid_drive_set(distance, speed, true);
  chassis.pid_wait();
}

void Reverse(float distance, int speed) {
  chassis.pid_drive_set(-distance, speed, true);
  chassis.pid_wait();
}

void FWDUntil(float distance, int speed, float untilDistance, int untilSpeed) {
  chassis.pid_drive_set(distance, speed, true);
  chassis.pid_wait_until(untilDistance);
  chassis.pid_speed_max_set(untilSpeed);
  chassis.pid_wait();
}

void revUntil(float distance, int speed, float untilDistance, int untilSpeed) {
  chassis.pid_drive_set(-distance, speed, true);
  chassis.pid_wait_until(-untilDistance);
  chassis.pid_speed_max_set(untilSpeed);
  chassis.pid_wait();
}

void turn(float heading, int speed) {
  chassis.pid_turn_set(heading, speed, true);
  chassis.pid_wait();
}

void turnUntil(float heading, int speed, float untilAngle, int untilSpeed) {
  chassis.pid_turn_set(heading, speed, true);
  chassis.pid_wait_until(untilAngle);
  chassis.pid_speed_max_set(untilSpeed);
  chassis.pid_wait();
}

void live_heading(void * ignore) {

  while (true) {
    std::cout << "Heading: " << chassis.drive_imu_get() << std::endl;
    pros::delay(250);
  }
  
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
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants, used for odom and non odom motions
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward without odom
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants
  chassis.pid_odom_angular_constants_set(6.5, 0.0, 52.5);    // Angular control for odom motions
  chassis.pid_odom_boomerang_constants_set(5.8, 0.0, 32.5);  // Angular control for boomerang motions

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);
  chassis.pid_odom_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 750_ms);
  chassis.pid_odom_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 750_ms);
  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  // The amount that turns are prioritized over driving in odom motions
  // - if you have tracking wheels, you can run this higher.  1.0 is the max
  chassis.odom_turn_bias_set(0.9);

  chassis.odom_look_ahead_set(7_in);           // This is how far ahead in the path the robot looks at
  chassis.odom_boomerang_distance_set(16_in);  // This sets the maximum distance away from target that the carrot point can be
  chassis.odom_boomerang_dlead_set(0.625);     // This handles how aggressive the end of boomerang motions are

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior for turning, this defaults it to the shortest path there
}


void red_right_rush() {
  //line up with line of tabs
  arm.move_relative(350, 100);
  Reverse(32.5, 150);
  turn(-29.4, 150);
  Reverse(16, 110);
  mogoClamp.set_value(true);
  pros::delay(100);
  turn(13, 110);
  intake.move_voltage(-12000);
  pros::delay(150);
  Forward(15, 110);
  pros::delay(700);
  mogoClamp.set_value(false);
  intake.move_voltage(12000);
  Reverse(8, 100);
  Forward(8, 100);
  pros::delay(200);
  turn(-97, 100);
  Reverse(23, 100);
  mogoClamp.set_value(true);
  intake.move_velocity(-12000);
  pros::delay(100);
  arm.move_relative(50, 100);
  turn(51, 100);
  intakeRelease.set_value(true);
  Forward(24, 100);
  intakeRelease.set_value(false);
  Reverse(10, 100);
  pros::delay(150);
  turn(130, 100);
  Forward(18, 60);
  //intake.move_voltage(0);

}

void red_right_win_point() {
  
  trapdoor.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  Forward(11, 90);
  arm.move_relative(-500, 100);
  pros::delay(500);
  Reverse(37, 90);
  arm.move_relative(-440, 100);
  mogoClamp.set_value(true);
  turn(-125, 100);
  intake.move_voltage(-12000);
  Forward(24.5, 90);
  arm.move_relative(500, 100);
  turn(36, 100);
  intakeRelease.set_value(true);
  Forward(44,90 );
  intakeRelease.set_value(false);
  Reverse(20, 90);
  turn(95, 100);
  Forward(11, 90);

}

void red_left_win_point() {
  //pros::Task heading(live_heading);

  trapdoor.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 127);
  basket.set_value(true);
  pros::delay(600);
  Forward(11, 127);
  arm.move_relative(-500, 127);
  pros::delay(500);
  Reverse(37, 65);
  mogoClamp.set_value(true);
  turn(120, 127);
  intake.move_voltage(-12000);
  Forward(23, 127);
  turn(219.5, 127);
  Forward(16, 127);
  pros::delay( 400);
  Reverse(16, 127);
  turn(190, 127);
  Forward(16.5, 127);
  pros::delay( 200);
  Reverse(18, 127);
  turn(295, 127);
  basket.set_value(false);
  Forward(38, 900);

}

void red_left_four() {
  arm.move_relative(300, 100);
  Reverse(22.3, 127);
  mogoClamp.set_value(true);
  intake.move_velocity(-12000);
  pros::delay(5);
  turn(126.5, 127);
  Forward(24, 127);
  Reverse(5.5, 127);
  turn(98, 127);
  Forward(12.5, 127);
  Reverse(10, 127);
  turn(12.5, 127);
  Forward(20.8, 127);
  Reverse(5, 127);
  turn(240, 127);
  Forward(39.5, 127);

}

void blue_right_win_point() {
  
  trapdoor.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 127);
  basket.set_value(true);
  pros::delay(600);
  Forward(11, 127);
  arm.move_relative(-500, 127);
  pros::delay(500);
  Reverse(37, 65);
  mogoClamp.set_value(true);
  turn(-120, 127);
  intake.move_voltage(-12000);
  Forward(23, 127);
  turn(-219.5, 127);
  Forward(16, 127);
  pros::delay( 400);
  Reverse(16, 127);
  turn(-190, 127);
  Forward(16.5, 127);
  pros::delay( 200);
  Reverse(18, 127);
  turn(-295, 127);
  basket.set_value(false);
  Forward(38, 900);
  
}
void blue_left_rush() {

  arm.move_relative(350, 100);
  Reverse(32.5, 150);
  turn(29.4, 150);
  Reverse(16.3, 110);
  mogoClamp.set_value(true);
  pros::delay(100);
  turn(-13, 127);
  intake.move_voltage(-12000);
  pros::delay(150);
  Forward(15, 127);
  pros::delay(700);
  mogoClamp.set_value(false);
  intake.move_voltage(12000);
  Reverse(8, 127);
  Forward(8, 127);
  pros::delay(200);
  turn(94.4, 127);
  Reverse(23, 127);
  mogoClamp.set_value(true);
  intake.move_velocity(-12000);
  pros::delay(100);
  arm.move_relative(50, 100);
  turn(-49, 127);
  intakeRelease.set_value(true);
  Forward(25.2, 127);
  intakeRelease.set_value(false);
  Reverse(10, 127);
  pros::delay(250);
  turn(-130, 127);
  Forward(16, 65);

}

void blue_left_win_point() {

  trapdoor.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 100);
  basket.set_value(true);
  pros::delay(1000);
  Forward(10.1, 90);
  arm.move_relative(-500, 100);
  pros::delay(500);
  Reverse(36.5, 80);
  arm.move_relative(-440, 100);
  mogoClamp.set_value(true);
  turn(125, 127);
  intake.move_voltage(-12000);
  Forward(24.5, 90);
  arm.move_relative(500, 100);
  turn(-36, 127);
  intakeRelease.set_value(true);
  Forward(44, 90);
  intakeRelease.set_value(false);
  Reverse(20, 127);
  turn(-95, 127);
  basket.set_value(false);
  Forward(16, 90);

}
void blue_right_four() {

  arm.move_relative(300, 100);
  Reverse(22.3, 127);
  mogoClamp.set_value(true);
  intake.move_velocity(-12000);
  pros::delay(5);
  turn(-126.5, 127);
  Forward(24, 127);
  Reverse(5.5, 127);
  turn(-98, 127);
  Forward(12.5, 127);
  Reverse(10, 127);
  turn(-12.5, 127);
  Forward(20.8, 127);
  Reverse(5, 127);
  turn(-240, 127);
  Forward(39.5, 127);

}

void skills() {
  //alliance stake
  basket.set_value(true);
  trapdoor.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 100);
  pros::delay(800);
  Forward(10, 100);
  arm.move_relative(-530, 100);
  pros::delay(100);
  Reverse(11, 100);
  //1st goal
  turn(79.5, 100);
  Reverse(20.2, 65);
  mogoClamp.set_value(true);
  turn(191, 100);
  basket.set_value(false);
  intake.move_voltage(-12000);
  Forward(22, 100);
  turn(231.5, 100);
  Forward(41.5, 100);
  Reverse(5, 100);
  turn(17.7, 100);
  Forward(23, 100);
  turn(-5, 100);
  Forward(36, 80);
  pros::delay(500);
  Reverse(18, 100);
  turn(-61, 100);
  pros::delay(100);
  Forward(13, 100);
  Reverse(12, 100);
  turn(136, 100);
  Reverse(19.6, 100);
  mogoClamp.set_value(false);
  Forward(10, 100);
  //2nd goal
  turn(267, 100);
  Reverse(75.5,75);
  mogoClamp.set_value(true);
  turn(170, 100);
  Forward(21, 100);
  turn(129, 100);
  Forward(38, 100);
  Reverse(5, 100);
  turn(-8, 100);
  Forward(23, 100);
  turn(-2.5, 100);
  Forward(35, 80);
  pros::delay(100);
  Reverse(23, 100);
  turn(53.2, 100);
  pros::delay(300);
  Forward(13, 100);
  pros::delay(100);
  Reverse(13, 100);
  turn(-145, 100);
  Reverse(26.3, 100);
  mogoClamp.set_value(false);
  intake.move_voltage(12000);
  Forward(15, 100);
  //3rd goal
  turn(-168, 100);
  Forward(87, 100);
  turn(-140, 100);
  Forward(28, 100);
  turn(-251, 100);
  Forward(53, 100);
  Reverse(20, 100);
  //4th goal
  turn( -90, 100);
  Forward(45, 100);
  turn(-115, 100);
  Forward(63, 100);
  Reverse(25, 100);
  //hang
  turn(34, 100);
  basket.set_value(false);
  pros::delay(100);
  arm.move_relative(770, 100);
  sweepArm.set_value(true);
  Forward(55, 85);
  Reverse(10, 100);

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