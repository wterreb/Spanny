#include "action.h"

StopWatch stopwatch(StopWatch::SECONDS);
StopWatch buzzerstopwatch(StopWatch::MILLIS);

Action::Action() {
}

//  Checks one speed zone at a time each time this is called
bool Action::processSpeed(int currentSpeed) {
   bool returnVal = false;
   if (currentZone < gZoneCount)
   {
      if ( isSpeedViolation(currentZone, currentSpeed)) {      
           returnVal = isTimeViolation(currentZone);       
      } 
      else {
         stopwatch.stop();
         stopwatch.reset();
         currentZone++;
      }
   }
   else {
      currentZone = 0;
   }

   if ( returnVal )  {
       if (buzzerToggle == false) {
          buzzerToggle = true;
          Serial.println("Start Buzzing");
       }
    } 
    else {
      if (buzzerToggle == true) {
          buzzerToggle = false;
          Serial.println("Stop Buzzing");  
      }
    }
    pulseBuzzer( buzzerToggle );
   return returnVal;
}

bool Action::isSpeedViolation(int zone, int speed) {
    bool returnVal = false;
    if ( (speed > gSpeedLimits[zone].lowerLimit) && (speed < gSpeedLimits[zone].upperLimit) ) {
         
         returnVal = true;
    }
    return returnVal;
}

bool Action::isTimeViolation(int zone) {
  bool returnVal = false; 
  if (stopwatch.elapsed() > (unsigned long)gSpeedLimits[zone].delaySeconds) {
     stopwatch.stop();
     returnVal = true;
  } else {
     stopwatch.start();
  }
  return returnVal; 
}

bool Action::pulseBuzzer(bool isInViolation) {
   if (isInViolation) {
       buzzerstopwatch.start();
       if (buzzerstopwatch.elapsed() < BUZZER_ON_TIME_MS) {
          buzzerState = true;
       }
       else { 
          if ( buzzerstopwatch.elapsed() < (BUZZER_ON_TIME_MS + BUZZER_OFF_TIME_MS) ) {      
              buzzerState = false;
          }
          else {
              buzzerstopwatch.stop();
              buzzerstopwatch.reset();
              buzzerstopwatch.start();
          }
       }
   }
   else {
      buzzerstopwatch.stop();
      buzzerstopwatch.reset();
   }
   pinMode(13, OUTPUT);
   digitalWrite(13, buzzerState);    // Flash onboard LED in sync with buzzer
   return buzzerState;
}



