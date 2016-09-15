
#ifndef __SETLIMITS_H__
#define __SETLIMITS_H__

//void GPS_printHelp( void );
void SET_RunCmd(  char *comand, char *args );
void SET_Details( void );
void SET_SpeedLimit( char* channel );

void showExistingSpeedLimits();


#endif //__SETLIMITS_H__
