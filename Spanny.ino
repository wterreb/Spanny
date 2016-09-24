#include "gps.h"

#include "shell.h"
#include "gpsdriver.h"
#include "storage.h"
#include "common.h"
#include "action.h"
//#include <avr/wdt.h>

#define GPS_TX      8
#define GPS_RX      9

//SoftwareSerial mySerial(GPS_TX, GPS_RX);
//Adafruit_GPS GPS(&mySerial);
Adafruit_GPS gps(&Serial1);
Gpsdriver gpsdriver(&gps);
Storage storage;
int nrZones;
Action action;
double fakeGpsSpeed;
boolean buzzerToggle = false;


void setup() {
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  gps.begin(9600);
  Serial1.begin(9600);
  Serial.begin(115200);
  SHELL_printHelp();
  nrZones = sizeof(speedLimits)/sizeof(speedLimits[0]); 
  storage.readSpeedLimits();
  
  
//  wdt_enable(WDTO_1S);
}

void loop() {
  if (SHELL_process() == 0)
  {
    char c = gps.read();

    if (c) {
      gpsdriver.ProcessLoop();
      if ( showNmea )  {
        Serial.print(c);
      }
    }

    double gpsspeed = gpsdriver.getSpeed();
    if (fakeGpsSpeed > 1.0) {
      gpsspeed = fakeGpsSpeed;    
    }
    if ( action.isAlertRequired( gpsspeed ) ) {
       if (buzzerToggle == false) {
          buzzerToggle = true;
          Serial.println("Buzzer On");
       }
      //  BuzzerOn
    } 
    else {
      if (buzzerToggle == true) {
          buzzerToggle = false;
          Serial.println("Buzzer Off");  
      }
    }
    if ( action.pulseBuzzer( buzzerToggle ) ) {
        // Beep now
    }


   
  }
//  wdt_reset();
}
