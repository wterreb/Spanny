
#ifndef __GPSDRIVER_H__
#define __GPSDRIVER_H__

#include <Arduino.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

#define GPS_TX      8
#define GPS_RX      9

class gpsdriver
{
public:
  boolean echoOn  = false;
  gpsdriver( Adafruit_GPS* gps );
  unsigned char tics;
  // methods
  double getLat( void);
  double getLng( void );
  char* getTime( void );
  int getTimeZone( void );
  double getSpeed( void );
  double getAltitude ( void );
  double getFixStatus ( void);
 // boolean setGpsEcho(boolean state);
 // boolean isGpsEchoOn( void );
  void setTimeZone(int timezone);
  void setUseMetric (bool state );
  void ProcessLoop( void );

private:
   
   int timezone = 0;
   bool useMetric = true;

 //  SoftwareSerial mySerial;
   Adafruit_GPS* GPS;

};
 


#endif
