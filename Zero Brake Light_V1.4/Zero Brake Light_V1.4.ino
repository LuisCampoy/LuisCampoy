
/*
Version: V1.4
Started April 18, 2022
Last Revision May 11, 2022

Inputs from the Zero will include:
  Driving light
  Brake (in the Zero, it goes low when brake is activated. WHen not activated is at +8V)
  

-------------------------------------------------------------------------------------------------------------------------
+12V system (will need 2 mosfets) and a connection bar to take inputs 
from bike (riding light, brake)
into arduino and outputs from arduino nano into Bike

Inputs from bike will have to be converted to +5V/ +3V3
Outputs from Arduino will have to be converted to +12V via mosfets
-------------------------------------------------------------------------------------------------------------------------

Design:

When Bike turns on:
  All lights will turn off and then
  L and R LED clusters will turn on (dimmed)

When Brake is activated:
  L and R LEDs will flash and then blink and then will go solid at full brightness (state machine for this)


Programming:
  Polling for brake signal or create hardware/ time interrupt at pin 0 or 1
  when signal is deactivated at whatever point within this loop it goes back to riding mode
  Boolean braking()
  Ledstate
  boolean function or hardware interrupt to check inputs from bike (brake)

  create objects:
    LED lights  

      State Machine with:
        
        ride (dimmed)
        Flashing (brake)
        Blinking (indicator)
        Solid (Full Brightness)

  
    Button
      will sense when a button is pressed
      This will eventually be the input from Bike

*/
 #include "bikeInputs.h" 
 #include "ledPanels.h"
// #include <Adafruit_SleepyDog.h>
 
 
//Global variables
int ledRight = 6;
int ledLeft = 5;
int brakePin = 7;
int initialize = 100;
 
//objects for bikeInputs, ledControls and chronos (will handle the timers. It is a separate tag, just in case I decide to include the indicators in the future)
bikeInputs inputs(brakePin);
ledPanels ledControls(ledLeft, ledRight);

 
void setup() {

 Serial.begin(9600);
// watchdogsetup();
 ledControls.allOff();

 Serial.print ("all off");

 delay (initialize);

 ledControls.rideMode();

 Serial.println("ride mode");

}

void loop() {

//====reset the watchdog on each loop===
//Watchdog.reset();

//this is based on polling for the brake signal and not on an interrupt
//attachInterrupt(digitalPinToInterrupt(brakePin), ledControls.brakeson(), RISING) //in the Zero it is normally at +8V. when brakes are activated it falls to +0V

  if (inputs.areBrakesActivated()) {
    ledControls.brakesRon();
  }
  else {
    ledControls.rideMode();

    Serial.println("ride mode");
  }

}

/*=====================================================
//sets up the watchdog for a 1 second timeout
//=====================================================*/
// void watchdogsetup(){
//   cli();
//   Watchdog.enable(1000);
//   sei();
// }


