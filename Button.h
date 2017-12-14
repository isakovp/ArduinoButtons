#if defined(ARDUINO)
#include "Arduino.h"
#endif

#ifndef BUTTON_H
#define BUTTON_H

#define DEBOUNCE_TIME 50
#define LONG_CLICK_TIME 300

class Button;
typedef void (*buttonEventHandler)(Button&);

class Button {

  public:
    Button(int btnPin);

    void scan();
    void setPressHandler(buttonEventHandler handler);
    void setUnPressHandler(buttonEventHandler handler);
    void setClickHandler(buttonEventHandler handler);
    void setLongClickHandler(buttonEventHandler handler);
    int getPin();
    void reset();
  private:
    int pin;
    int prevButtonState;
    int buttonState;
    long lastDebounceTime;
    long pressTime;
    buttonEventHandler c_handler;
    buttonEventHandler p_handler;
    buttonEventHandler up_handler;
    buttonEventHandler cl_handler;


};
#endif

