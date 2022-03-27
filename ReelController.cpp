#include "ReelController.hpp"

float ReelController::readSpeed() const {
  return _reel1.readFloat("encoder.vel_estimate");
}

void ReelController::setIdle() {
  _isPlaying = false;

 // _reel0.write("controller.config.enable_torque_mode_vel_limit", 0);
  //_reel1.write("controller.config.enable_torque_mode_vel_limit", 0);
  _reel0.write("controller.config.input_mode", 1);
  _reel1.write("controller.config.input_mode", 1);
  _reel0.write("controller.config.control_mode", CONTROL_MODE_TORQUE_CONTROL);
  _reel1.write("controller.config.control_mode", CONTROL_MODE_TORQUE_CONTROL);
  _reel0.write("controller.config.vel_integrator_gain", 30);
  _reel1.write("controller.config.vel_integrator_gain", 30);
  _reel0.write("controller.config.pos_gain", 30);
  _reel1.write("controller.config.pos_gain", 30);
  _reel0.write("controller.config.vel_gain", 1);
  _reel1.write("controller.config.vel_gain", 1);
  _reel0.write("controller.input_vel", 0);
  _reel1.write("controller.input_vel", 0);
  _reel0.write("controller.input_torque", 0.12f);
  _reel1.write("controller.input_torque", -0.12f);
}

void ReelController::play() {
  _isPlaying = true;
  //_reel0.write("controller.config.enable_torque_mode_vel_limit", 0);
  _reel0.write("controller.config.vel_integrator_gain", 20);
  _reel1.write("controller.config.vel_integrator_gain", 225);
  _reel0.write("controller.config.pos_gain", 20);
  _reel1.write("controller.config.pos_gain", 20);
  _reel0.write("controller.config.vel_gain", 1);
  _reel1.write("controller.config.vel_gain", 1);
  _reel0.write("controller.config.control_mode", CONTROL_MODE_TORQUE_CONTROL);
  _reel0.write("controller.input_torque", 0.12);
  _reel0.write("controller.input_vel", 0);
  _reel1.write("controller.config.input_mode", INPUT_MODE_VEL_RAMP);
  _reel1.write("controller.config.control_mode", CONTROL_MODE_VELOCITY_CONTROL);
  _reel1.write("controller.config.vel_ramp_rate", 0.7);
  _reel1.write("controller.input_torque", 0);

  _reel1.write("controller.input_vel", initialPlaySpeed);
  _currentPlaySpeed = initialPlaySpeed;
}

void ReelController::stop() {
  _isPlaying = false;
  _reel0.write("controller.config.vel_integrator_gain", 10);
  _reel1.write("controller.config.vel_integrator_gain", 10);
  _reel0.write("controller.config.pos_gain", 20);
  _reel1.write("controller.config.pos_gain", 20);
  _reel0.write("controller.config.vel_gain", 0.6); 
  _reel1.write("controller.config.vel_gain", 0.6);
  _reel0.write("controller.input_torque", 0);
  _reel1.write("controller.input_torque", 0);
  _reel0.write("controller.input_vel", 0);
  _reel1.write("controller.input_vel", 0);
}

void ReelController::rewind() {
  _isPlaying = false;
  _reel1.write("controller.config.input_mode", 1);
  _reel0.write("controller.config.vel_integrator_gain", 10);
  _reel1.write("controller.config.vel_integrator_gain", 10);
  _reel0.write("controller.config.pos_gain", 20);
  _reel1.write("controller.config.pos_gain", 20);
  _reel0.write("controller.config.vel_gain", .6);
  _reel1.write("controller.config.vel_gain", .6);
  _reel1.write("controller.config.control_mode", CONTROL_MODE_TORQUE_CONTROL);
  _reel1.write("controller.input_torque", -0.1);
  _reel1.write("controller.input_vel", 0);
  _reel0.write("controller.config.input_mode", INPUT_MODE_VEL_RAMP);
  _reel0.write("controller.config.control_mode", CONTROL_MODE_VELOCITY_CONTROL);
  _reel0.write("controller.config.vel_ramp_rate", 1.5);
  _reel0.write("controller.input_torque", 0);
  _reel0.write("controller.input_vel", rewindSpeed);
}

void ReelController::fastForward() {
  _isPlaying = false;
  _reel0.write("controller.input_vel", 0);
  _reel1.write("controller.input_vel", 0);
  _reel0.write("controller.config.vel_integrator_gain", 10);
  _reel1.write("controller.config.vel_integrator_gain", 10);
  _reel0.write("controller.config.pos_gain", 20);
  _reel1.write("controller.config.pos_gain", 20);
  _reel0.write("controller.config.vel_gain", 2);
  _reel1.write("controller.config.vel_gain", 1);
  _reel0.write("controller.config.control_mode", CONTROL_MODE_TORQUE_CONTROL);
  _reel0.write("controller.input_torque", 0.1);
  _reel0.write("controller.input_vel", 0);
  _reel1.write("controller.config.input_mode", INPUT_MODE_VEL_RAMP);
  _reel1.write("controller.config.control_mode", CONTROL_MODE_VELOCITY_CONTROL);
  _reel1.write("controller.config.vel_ramp_rate", 1.5);
  _reel1.write("controller.input_torque", 0);
  _reel1.write("controller.input_vel", fastForwardSpeed);
}

void ReelController::setPlaySpeed(double value) {
  if (_isPlaying && _currentPlaySpeed != value)
    _reel1.write("controller.input_vel", value);
  _currentPlaySpeed = value;
}
