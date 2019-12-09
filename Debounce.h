#ifndef Debounce_h
#define Debounce_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

class Debounce {
  public:
    Debounce(uint8_t pin, unsigned long debounceDelay);
    void attach();
    boolean pressed();

    private:
      uint8_t _pin;
      unsigned long _dobounceDelay;
      unsigned long _lastDebounceTime;
      int _buttonState;
      int _lastButtonState;
};

#endif
