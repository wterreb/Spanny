
#ifndef __GPS_H__
#define __GPS_H__

//void GPS_printHelp( void );
void GPS_RunCmd(  char *comand, char *args );
void GPS_Details( void );
void GPS_FixStatus( void );
void GPS_Lat( void);
void GPS_Lng( void);
void GPS_Speed( void );
void GPS_Altitude( void );
void printTimeZone( void );
void GPS_Time( void );
void GPS_Verbose( char* param );
void GPS_TimeZone( char* param );


#endif //__GPS_H__
