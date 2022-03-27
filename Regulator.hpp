#pragma once

class Regulator {
public:
  void setSetpoint(double value) {
    _setpoint = value;
  }

  void setOutputRange(double minOutput, double maxOutput) {
    _minOutput = minOutput;
    _maxOutput = maxOutput;
  }

  double compute(double currentOutput, double input) {
    unsigned long now = millis();
    unsigned long elapsed = now - lastTime;
    double newOutput = currentOutput;
    if (elapsed >= 100) {
      lastTime = now;
      if (input * 0.9 < _setpoint) newOutput *= 1.1;
      if (input * 1.1 > _setpoint) newOutput *= 0.9;
    }
    if (newOutput > _maxOutput) newOutput = _maxOutput;
    if (newOutput < _minOutput) newOutput = _minOutput;
    return newOutput;
  }

private:
  double _minOutput, _maxOutput, _setpoint;
  unsigned long lastTime = 0;
};
