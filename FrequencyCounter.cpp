#include "FrequencyCounter.hpp"

#include <Arduino.h>

static volatile double frequency; // in Hz

static void interrupHandler() {
  static unsigned long lastTimestamp = 0;

  unsigned long timestamp = micros();
  unsigned long elapsed = timestamp - lastTimestamp;

  // Ignore frequencies below 1Hz and above 1kHz
  if (1000 < elapsed && elapsed < 1000000) {
    frequency = 1e6 / elapsed;
  }

  lastTimestamp = timestamp;
}

void FrequencyCounter::begin() {
  pinMode(_pin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(_pin), interrupHandler, RISING);
}

double FrequencyCounter::getFrequency() {
  return frequency;
}
