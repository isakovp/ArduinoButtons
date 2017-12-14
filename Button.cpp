
#include "Button.h"

Button::Button(int btnPin) {
  pin = btnPin;
  prevButtonState = LOW;
  lastDebounceTime = 0;
}

int Button::getPin() {
  return pin;
}

void Button::reset() {
  prevButtonState = LOW;
  lastDebounceTime = 0;
  p_handler = NULL;
  c_handler = NULL;
  cl_handler = NULL;
  up_handler = NULL:
}  

void Button::scan(void) {
  if (p_handler != NULL || c_handler != NULL) {
    int currentState = digitalRead(pin);

    if (currentState != prevButtonState) {
      lastDebounceTime =  millis();
    }

    if ((millis() - lastDebounceTime) > DEBOUNCE_TIME) {

     if (currentState != buttonState) {
        buttonState = currentState;

        if (buttonState == HIGH) {
          pressTime = millis();
          if (p_handler != NULL) {
            p_handler(*this);
          }
        }


        if (buttonState == LOW) {
          if (millis() - pressTime > LONG_CLICK_TIME) {
            pressTime = millis();
            if (cl_handler != NULL) {
              cl_handler(*this);
            }
          } else {
            if (c_handler != NULL) {
              c_handler(*this);
            }
          }
          if (up_handler != NULL) {
            up_handler(*this);
          }
        }
      }
    }
    prevButtonState = currentState;
  }
}

void Button::setPressHandler(buttonEventHandler h) {
  p_handler = h;
}

void Button::setUnPressHandler(buttonEventHandler h) {
  up_handler = h;
}

void Button::setClickHandler(buttonEventHandler h) {
  c_handler = h;
}

void Button::setLongClickHandler(buttonEventHandler h) {
  cl_handler = h;
}
