#pragma once

// CAUTION: current design only allows on instance
// TODO: the frequency should go back to zero when no interrupt is triggered
class FrequencyCounter {
public:
  FrequencyCounter(int pin) : _pin(pin) {
    // Not sure if calling pinMode() and attachInterrupt() was allowed before setup()
    // so I prefer not calling them in the constructor
  }

  void begin();
  double getFrequency();

private:
  int _pin;
};
