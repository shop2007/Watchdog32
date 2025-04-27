#ifndef WATCHDOG32_H
#define WATCHDOG32_H

#include <Arduino.h>

// if the breakout mounts a pnp transistor, define TransistorPNP before including the library
// #define TransistorPNP 1


class Watchdog32 {
public:
  // Constructor
  Watchdog32();

  // Initialization method
  void begin(uint8_t triggerPin, uint8_t enablePin);

  // Methods to manage the watchdog
  void disable();
  void enable();
  void retrigger();

private:
  uint8_t _triggerPin;
  uint8_t _enablePin;
};

#endif
