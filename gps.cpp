#include "Arduino.h"
#include "gps.h"
#include "utils.h"
//#include "shared.h"
#include "shellutils.h"
#include "common.h"

#define TEST_NAME GPS
SHELL_INCLUDE_BEFORE_DEFINITIONS( TEST_NAME )

// No variables
static store_t vars[ 0 ] = { };
static const unsigned int defaults [ 0 ] = { };


static functions_t funcs[] = {
    { "help",      SHELL_COMMAND PrintHelp,              "This help" },
    { "vars",      SHELL_COMMAND PrintVars,              "Display variable values" },
    { "details",   SHELL_COMMAND GPS_Details,            "General GPS info" },
    { "fixstatus", SHELL_COMMAND GPS_FixStatus,          "GPS info" },
    { "lat",       SHELL_COMMAND GPS_Lat,                "Latitude" },
    { "lng",       SHELL_COMMAND GPS_Lng,                "Longtitude" },
    { "speed",     SHELL_COMMAND GPS_Speed,              "Speed in km/h" },
    { "alti",      SHELL_COMMAND GPS_Altitude,           "Altitude in m" },
    { "time",      SHELL_COMMAND GPS_Time,               "Time (local time zone)" },
    { "verbose",   SHELL_COMMAND GPS_NMEA,               "Show/hide NMEA strings. Example : 'gps verbose on/off'" },
    { "timezone",  SHELL_COMMAND GPS_TimeZone,           "Sets timezone.  Example : 'gps tzone -10' sets TZ to GMT-10" },
    {}
};

SHELL_INCLUDE_AFTER_DEFINITIONS( TEST_NAME )

void GPS_RunCmd( char *command, char *args ) {
    SHELLUTILS_RunCommand( command, args, &all );
}

void GPS_Details( void ) {
    Serial.println("GPS Details");
}

void GPS_FixStatus( void ) {
   Serial.print("fix = "); Serial.println(fix);
   Serial.print("fixquality = "); Serial.println(fixquality);
   Serial.print("satellites = "); Serial.println(satellites);
}
 
void GPS_Lat( void) {
  Serial.println("Latitude");
}

void GPS_Lng( void) {
  Serial.println("Longitude");
}

void GPS_Speed( void ) {
  Serial.println("Speed");
}

void GPS_Altitude( void ) {
  Serial.println("Altitude");
}
void printTimeZone( void ) {
  Serial.print("GMT");
  if ( timezone > 0 ) {
    Serial.print("+");
  }
  Serial.print(timezone);
}

void GPS_Time( void ) {
  Serial.print("Time ");
  
   uint8_t hourTZ = hour + timezone;
   if (hourTZ < 0) { 
      hourTZ += 24; 
      day = day+1;
      if (day > 31) {
         day = 1;
         month = month+1;
      }
   }
   if (hourTZ == 24) { 
       hourTZ = 24 - hourTZ; 
       day = day+1;
   }
   char buffer[30];
   sprintf(buffer, "%02d/%02d/%d %02d:%02d:%02d",day,month,year,hourTZ,minute,seconds);
   Serial.print(buffer);
   Serial.print(" ");
   printTimeZone();
   Serial.println("");
}

void GPS_NMEA( char* param ) {
  Serial.println();
  if ( strcmp(param, "on")==0 || strcmp(param, "true")==0|| strcmp(param, "1")==0 ) {
    showNmea = true;
   // gpsdriver.echoOn = true;
    Serial.println("Verbose mode enabled");
  }
  else {
     showNmea = false;
   //  gpsdriver.echoOn = false;
     Serial.println("Verbose mode disabled");
  }
    
}

void GPS_TimeZone( char* param ) {
  if (param != NULL) {
     timezone = SHELLUTILS_getLongValue(param);
  }
  printTimeZone();
  
}

