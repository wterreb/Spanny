#ifndef __ACTION_H__
#define __ACTION_H__

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include "stopwatch.h"
#include "common.h"
//#include <SoftwareSerial.h>

#define GPS_TX      8
#define GPS_RX      9

class Action
{
public:
  Action( );
  bool processSpeed(int currentSpeed);
  
  
private:
  bool isTimeViolation(int zone);
  bool isSpeedViolation(int zone, int speed);
  bool pulseBuzzer(bool isInViolation);
  int currentZone = 0;
  boolean buzzerState = false;
  boolean buzzerToggle = false;
  unsigned long BUZZER_ON_TIME_MS = 100;
  unsigned long  BUZZER_OFF_TIME_MS = 200;
};
 


#endif
