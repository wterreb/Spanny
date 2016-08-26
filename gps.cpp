#include "Arduino.h"
#include "utils.h"
#include "gps.h"
#include "shared.h"


command_t GpsCommands[] = {
    { "help",        GPS_printHelp,          "This command" },
  //  { "info",      GPS_Info,               "General GPS info" },
  //  { "lat",       GPS_Lat,                "Latitude" },
  //  { "lng",       GPS_Lng,                "Longtitude" },
  //  { "speed",     GPS_Speed,              "Speed in km/h" },
  //  { "alti",      GPS_Altitude,           "Altitude in m" },
  //  { "timeGMT",   GPS_TimeGMT,            "Time in GMT" },
  //  { "time",      GPS_Time,               "Time in timezone" },
    {}
};

//-----------------------------------------------------------------------------------------------------------------

static void GPS_PrintHelp ( char *, char * ) {
    Serial.println( "Spanny GPS Help" );
    Serial.println( "------------------" );
    Serial.println( "" );
     for ( int i=0; i<ARRAY_LENGTH( GpsCommands ); i++ ) {
        Serial.print( GpsCommands[i].name );
        Serial.print( " - " );
        Serial.println( GpsCommands[i].description );
    }
}

//-----------------------------------------------------------------------------------------------------------------
void GPS_printHelp ( void ) {
    printHelp( "", "" );
};
