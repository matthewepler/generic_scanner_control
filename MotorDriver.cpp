#include "MotorDriver.h"

float MotorDriver::readFloat(const char *param) const {
  _serial.printf("r axis%d.%s\n", _axis, param);
  return _serial.readString().toFloat();
}

void MotorDriver::write(const char *param, int value) {
  _serial.printf("w axis%d.%s %d\n", _axis, param, value);
}

void MotorDriver::write(const char *param, double value) {
  _serial.printf("w axis%d.%s %f\n", _axis, param, value);
}
