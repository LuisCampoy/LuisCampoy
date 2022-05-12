

#ifndef ledPanels_h_
#define ledPanels_h_

#include "chronos.h"  //the startTimer function is passing the duration parameter. If I decide to add turn signals this function will also pass the turn signal timer variable)

class ledPanels {


  int _leftLED;
  int _rightLED;
  unsigned long _chronoFlashing = 1000;  //duration of the initial flashing during braking
  unsigned long _chronoBlinking = 2000;  //duration of the initial blinking during braking


  //State Machine for brakingMode

  enum {
    DIMMED,
    FLASHING,
    BLINKING,
    SOLID
  } _currentState;

  chronos timers;  //create object here?

public:
  //constructor

  ledPanels(int leftLED, int rightLED) {
    _leftLED = leftLED;
    _rightLED = rightLED;

    pinMode(_leftLED, OUTPUT);
    pinMode(_rightLED, OUTPUT);
  }

  //public methods

  void allOff() {
    digitalWrite(_leftLED, LOW);
    digitalWrite(_rightLED, LOW);
  }

  void rideMode() {
    analogWrite(_leftLED, dimmed);
    analogWrite(_rightLED, dimmed);
  }

  void brakesRon() {
    //goes dimmed, then flashing (for TIMER_FLASHING seconds), then blinking (for TIMER_BLINKING seconds), then full brightness until input (buuton is no longer pressed) changes to LOW/false


    switch (_currentState) {

      case DIMMED:
        _currentState = FLASHING;

        Serial.println("DIMMED mode");
        //delay (5000); //for debugging purposes
        timers.startTimer(_chronoFlashing);  //passing the parameter for the duration of the flashing mode
        
        break;

      case FLASHING:

        Serial.println("FLASHING mode");

        bothFlashing();
          if (timers.isTimerReady()) {  // if true it will change states, if false it will stay in the current state
          _currentState = BLINKING;
         //delay (5000); //for debugging purposes
          timers.startTimer(_chronoBlinking);  //passing the parameter for the duration of the blinking mode
        }
       
        break;

      case BLINKING:

        Serial.println("BLINKING mode");

        bothBlinking();
           if (timers.isTimerReady()) {
          _currentState = SOLID;
         
           }
                
        break;

      case SOLID:

        Serial.println("SOLID mode");

        bothFull();
        break;
    }
  }

private:
  int dimmed = 50;

  void bothFull() {
    digitalWrite(_leftLED, HIGH);
    digitalWrite(_rightLED, HIGH);
  }

  void bothFlashing() {
   static unsigned long previousMillis = millis();

    int flashingfrequency = 40;  //in Hz
    int interval = 1000 / flashingfrequency;

    if (millis() - previousMillis > interval) {

      digitalWrite(_leftLED, !digitalRead(_leftLED));
      digitalWrite(_rightLED, !digitalRead(_rightLED));
      previousMillis = millis();
    }
  }
  void bothBlinking() {
    static unsigned long previousMillis = millis();
    int blinkingfrequency = 4;  //in Hz
    int interval = 1000 / blinkingfrequency;

    if (millis() - previousMillis > interval) {

      digitalWrite(_leftLED, !digitalRead(_leftLED));
      digitalWrite(_rightLED, !digitalRead(_rightLED));
      previousMillis = millis();
    }
  }
};

#endif