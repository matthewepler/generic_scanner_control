#pragma once

#include <Arduino.h>
#include <ODriveArduino.h>

class MotorDriver {
public:
  MotorDriver(Stream &serial, int axis) : _serial(serial), _axis(axis) {}

  void write(const char *param, int value);
  void write(const char *param, double value);

  float readFloat(const char *param) const;

private:
  Stream &_serial;
  int _axis;
};