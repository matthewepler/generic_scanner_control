#pragma once

#include <Arduino.h>

#include "MotorDriver.h"

class ReelController {
public:
  ReelController(Stream &serial) : _reel0(serial, 0), _reel1(serial, 1), _isPlaying(false), _currentPlaySpeed(0) {}

  float readSpeed() const;

  void setIdle();
  void play();
  void stop();
  void rewind();
  void fastForward();

  void setPlaySpeed(double);

  double getPlaySpeed() const {
    return _currentPlaySpeed;
  }

  bool isPlaying() const {
    return _isPlaying;
  }

  const double initialPlaySpeed = -0.7;
  const double rewindSpeed = 2.5;
  const double fastForwardSpeed = -2.5;

private:
  MotorDriver _reel0, _reel1;
  bool _isPlaying;
  double _currentPlaySpeed;
};
