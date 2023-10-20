#include "main.h"

extern pros::Motor& PTO_left;
extern pros::Motor& PTO_right;
extern pros::ADIDigitalOut PTO_piston;
extern pros::Motor intake_left;
extern pros::Motor intake_right;
extern pros::Motor catapult_left;
extern pros::Motor catapult_right;

const int INTAKE_SPEED = 127;
const int CATAPULT_SPEED = 127;
const int RELATIVE_CHARGE_DIST = 720;
const int RELATIVE_SHOOT_DIST = 50;

bool pto_endgame_enabled = false;
float pto_cooldown = 0;
bool intake_toggle_enabled = false;

void rumble_controller() {
  master.rumble("....");
}

void print_stats_controller() {
  // Clear the controller screen
  master.clear();

  // Print PTO mode
  if (pto_endgame_enabled) {
    master.set_text(0, 0, "4 motor");
  } else {
    master.set_text(0, 0, "6 motor");
  }
}

void toggle_endgame(bool toggle){
  // Only use endgame if PTO is in 4 motor mode
  if(!pto_endgame_enabled) return;

  // Set the endgame motors to the correct position
  if(toggle){
    // TODO turn on the endgame
  } else{
    // TODO turn off the endgame
  }
}

void move_catapult(int degrees) {
  catapult_left.move_relative(degrees, CATAPULT_SPEED);
  catapult_right.move_relative(degrees, CATAPULT_SPEED);
}

void charge_catapult() {
  // Charge the catapult (not likely to be used often)
  move_catapult(RELATIVE_CHARGE_DIST);
}

void shoot_catapult() {
  // Shoot the catapult and recharge it
  move_catapult(RELATIVE_SHOOT_DIST + RELATIVE_CHARGE_DIST);
  return;
}

void spin_intake_for(float dist) {
  intake_left.move_relative(dist, INTAKE_SPEED);
  intake_right.move_relative(dist, INTAKE_SPEED);
}

void set_intake_volts(int volts) {
  intake_left.move_voltage(volts);
  intake_right.move_voltage(volts);
}

void pto_toggle(bool toggle) {
  // This prevents extreme air loss using a cooldown
  if (pto_cooldown > 0) {
    return;
  }
  // Set the PTO cooldown
  pto_cooldown = ez::util::DELAY_TIME * 50;
  
  // Toggle PTO motors + bool
  pto_endgame_enabled = toggle;
  chassis.pto_toggle({PTO_left, PTO_right}, toggle);

  // Actuate the piston 
  PTO_piston.set_value(!toggle);
}

void set_pto_volts(int volts) {
  // Only activates if engame is enabled
  if (!pto_endgame_enabled)
    return;
  
  // Sets endgame voltage to the input value
  PTO_left = volts;
  PTO_right = volts;
}

void intake_control() {
  // Toggle the intake (inward direction only)
  if (master.get_digital_new_press(DIGITAL_R1) || master.get_digital_new_press(DIGITAL_R2)) {
    intake_toggle_enabled = !intake_toggle_enabled;
  }

  // If toggled, intake stays on
  if (intake_toggle_enabled) {
    set_intake_volts(12000);
    return;
  }

  // Hold buttons to control the intake (while not toggled)
  if (master.get_digital(DIGITAL_L1)) {
    set_intake_volts(12000);
  } else if (master.get_digital(DIGITAL_L2)) {
    set_intake_volts(-12000);
  } else {
    set_intake_volts(0);
  }
}

void pto_control() {
  // Handle PTO activation/deactivation
  if (master.get_digital(DIGITAL_A))
    pto_toggle(!pto_endgame_enabled);
  else if (master.get_digital(DIGITAL_DOWN))
    pto_toggle(0);
  else if (master.get_digital(DIGITAL_UP))
    pto_toggle(1);
}