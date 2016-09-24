#include "gps.h"

#include "shell.h"
#include "gpsdriver.h"
#include "storage.h"
#include "common.h"
//#include <avr/wdt.h>

#define GPS_TX      8
#define GPS_RX      9

//SoftwareSerial mySerial(GPS_TX, GPS_RX);
//Adafruit_GPS GPS(&mySerial);
Adafruit_GPS GPS(&Serial1);
gpsdriver gpsprocess(&GPS);
storage eeprom;


void setup() {
  // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
  GPS.begin(9600);
  Serial1.begin(9600);
  Serial.begin(115200);
  SHELL_printHelp();
  eeprom.readSpeedLimits();
//  wdt_enable(WDTO_1S);
}

void loop() {
  if (SHELL_process() == 0)
  {
    char c = GPS.read();

    if (c) {
      gpsprocess.ProcessLoop();
      if ( showNmea )  {
        Serial.print(c);
      }
    }
  }
//  wdt_reset();
}
