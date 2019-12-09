#include "Debounce.h"

uint8_t _pin;
unsigned long _debounceDelay;
unsigned long _lastDebounceTime;
int _buttonState;
int _lastButtonState = LOW;

Debounce::Debounce(uint8_t pin, unsigned long debounceDelay) {
  _pin = pin;
  _debounceDelay = debounceDelay;
  _lastDebounceTime = 0;
}

void Debounce::attach() {
  pinMode(_pin, INPUT);
}

boolean Debounce::pressed() {
  int reading = digitalRead(_pin);

  if (reading != _lastButtonState) {
    _lastDebounceTime = millis();
  }

  if ((millis() - _lastDebounceTime) > _debounceDelay) {
    if (reading != _buttonState) {
      _buttonState = reading;

       if(_buttonState == HIGH) {
        _lastButtonState = reading;
        return true;
       }
    }
  }

  _lastButtonState = reading;
  return false;
}
