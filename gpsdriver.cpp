#include <Adafruit_GPS.h>

#include "gpsdriver.h"
#include "common.h"

uint8_t hour, minute, seconds, year, month, day;
float latitude, longitude;
float altitude, speed, angle, magvariation, HDOP;
boolean fix;
uint8_t fixquality, satellites;



// Member functions definitions including constructor
Gpsdriver::Gpsdriver(  Adafruit_GPS* gps ) {
   GPS = gps;
}

//  This gets called as often as possible from the main loop
 void Gpsdriver::ProcessLoop( void ) {      
    // if a sentence is received, we can process it now
    if (GPS->newNMEAreceived()) {  
        if (!GPS->parse(GPS->lastNMEA())) {  // this also sets the newNMEAreceived() flag to false
                return;  // we can fail to parse a sentence in which case we should just wait for another
        }
        else {
          hour = GPS->hour;
          minute = GPS->minute;
          seconds = GPS->seconds;
          year = GPS->year;
          month = GPS->month;
          day = GPS->day;

          altitude = GPS->altitude;
          speed = 1.852 * GPS->speed;
          angle = GPS->angle;
          magvariation = GPS->magvariation;
          HDOP = GPS->HDOP;;
        }
    }
 }
 
 double Gpsdriver::getSpeed( void ) {
    return 1.852 * GPS->speed;
 }


