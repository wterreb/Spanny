#include "gps.h"

#include "shell.h"
#include "gpsdriver.h"
#include "storage.h"
#include "common.h"
#include "action.h"
#include <avr/wdt.h>

#define GPS_TX      8
#define GPS_RX      9

//SoftwareSerial mySerial(GPS_TX, GPS_RX);
//Adafruit_GPS GPS(&mySerial);
Adafruit_GPS gps(&Serial1);
Gpsdriver gpsdriver(&gps);
bool gShowNmea = false;
bool gBuzzOnce = false;

Action action;
double gFakeGpsSpeed;
Speedlimit_t gSpeedLimits[10];
Settings_t gSettings;
Storage storage;
int gZoneCount  = sizeof(gSpeedLimits)/sizeof(gSpeedLimits[0]); 

void setup() {
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  gps.begin(9600);
  Serial1.begin(9600);
  Serial.begin(115200);
  SHELL_printHelp();
  wdt_enable(WDTO_1S);
}

void loop() {
  if (SHELL_process() == 0)
  {
    char c = gps.read();
    if (c) {
      gpsdriver.ProcessLoop();
      if ( gShowNmea )  {
        Serial.print(c);
      }
    }
    double gpsspeed = gpsdriver.getSpeed();
    if (gFakeGpsSpeed > 1.0) {
      gpsspeed = gFakeGpsSpeed;    
    }
    action.processSpeed( gpsspeed );
  }
  wdt_reset();
}
