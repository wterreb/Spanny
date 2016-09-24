#ifndef __COMMON_H__
#define __COMMON_H__

#include "shared.h"

extern uint8_t hour, minute, seconds, year, month, day;
extern float latitude, longitude;
extern float altitude, speed, angle, magvariation, HDOP;
extern boolean fix;
extern uint8_t fixquality, satellites;

extern bool showNmea;
extern int8_t timezone;
extern speedlimit speedLimits[10];
extern int nrZones;
extern double fakeGpsSpeed;


#endif
