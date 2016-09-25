#ifndef __COMMON_H__
#define __COMMON_H__

#include "shared.h"

extern uint8_t hour, minute, seconds, year, month, day;
extern float latitude, longitude;
extern float altitude, speed, angle, magvariation, HDOP;
extern boolean fix;
extern uint8_t fixquality, satellites;

extern bool gShowNmea;
extern bool gBuzzOnce;
extern Speedlimit_t gSpeedLimits[10];
extern Settings_t gSettings;
extern int gZoneCount;
extern double gFakeGpsSpeed;

#endif
