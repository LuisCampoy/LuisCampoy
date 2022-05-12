#ifndef chronos_h_
#define chronos_h_

class chronos {
  unsigned long previousMillis=0;
  unsigned long timerTarget;


public:

  void startTimer (unsigned long eventDuration){ //this will receive the argument for each of the different timers (flashing and blinking and perhaps the indicators in the future)
  previousMillis = millis(); 
  timerTarget = eventDuration; //interval
   }

  //checks if Timer is ready
  bool isTimerReady() { 
    unsigned long currentMillis = millis(); // if static unsigned long, state machine never goes to blinking or solid but it would flash every time
    return (currentMillis - previousMillis) > timerTarget;
      }
  
  };

#endif