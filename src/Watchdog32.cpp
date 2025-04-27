#include "Watchdog32.h"

Watchdog32::Watchdog32()
  : _triggerPin(255), _enablePin(255) // invalid values ​​until called begin()
{
}

void Watchdog32::begin(uint8_t triggerPin, uint8_t enablePin) {
  _triggerPin = triggerPin;
  _enablePin = enablePin;

  pinMode(_triggerPin, OUTPUT);
  pinMode(_enablePin, OUTPUT);

  disable();
}

void Watchdog32::disable() {
  #ifdef TransistorPNP
    digitalWrite(_enablePin, HIGH);
  #else
    digitalWrite(_enablePin, LOW);
  #endif
}

void Watchdog32::enable() {
  #ifdef TransistorPNP
    digitalWrite(_enablePin, LOW);
  #else
    digitalWrite(_enablePin, HIGH);
  #endif
}

void Watchdog32::retrigger() {
  digitalWrite(_triggerPin, HIGH);
  delay(40);
  digitalWrite(_triggerPin, LOW);
  delay(5);
}
