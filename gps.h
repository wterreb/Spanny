
#ifndef __GPS_H__
#define __GPS_H__

//#include "shellutils.h"

void GPS_printHelp( void );
/*
#define GPS_INCLUDE_BEFORE_DEFINITIONS( name ) \
   void GPS_PrintHelp( void );
   
#define GPS_INCLUDE_AFTER_DEFINITIONS( name ) \
    shellType_t const all = { .pFuncs = funcs, .numFuncs = ARRAY_LENGTH( funcs ), \
            .pVars = vars, .pDefaults = (unsigned int *)defaults, \
            .numVars = ARRAY_LENGTH( vars ) }; \
    static void PrintHelp( void ) { GPS_PrintHelp( &all ); } \   
*/
#endif __GPS_H__
