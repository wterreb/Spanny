#include "gps.h"
#include "shell.h"
#include "gpsdriver.h"
#include "common.h"

#define GPS_TX      8
#define GPS_RX      9

SoftwareSerial mySerial(GPS_TX, GPS_RX);
Adafruit_GPS GPS(&mySerial);
gpsdriver gpsprocess(&GPS);



void setup() {
     // 9600 NMEA is the default baud rate for Adafruit MTK GPS's- some use 4800
   GPS.begin(9600);
   Serial.begin(115200);
   SHELL_printHelp();
}

void loop() {
    SHELL_process();

    char c = GPS.read();

    if (c) {
        gpsprocess.ProcessLoop();
        if ( showNmea )  {
           Serial.print(c);
        }
    }
    
    
}
