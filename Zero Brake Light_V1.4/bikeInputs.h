

#ifndef bikeInputs_h_
#define bikeInputs_h_

#include "chronos.h"

class bikeInputs {

  int _brake;


public:

  //constructor
  bikeInputs(int brake) { //brake pin is the argument
    _brake = brake;
    pinMode(_brake, INPUT);
  }

  bool areBrakesActivated() {
    volatile long currentMillis = millis();
    static long previousMillis;
    static int last;
    int state = digitalRead(_brake);
    bool ret = false;

    if (last != state) {
      previousMillis = currentMillis;
      last = state;
    }

    if ((currentMillis - previousMillis) > deBounce) {
    ret = last == false; //could be false or HIGH...not sure
   
    }

  return ret;

  Serial.println("brake detected");
 }

private:
int deBounce=100;
};

#endif