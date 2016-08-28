
#ifndef __SHELL_H__
#define __SHELL_H__
#include "gpsdriver.h"


static const unsigned int LINE_BUFFER_SIZE = 50;

void SHELL_printHelp( void );
void SHELL_processLine( char *line  );
void SHELL_process( void );

#endif /* __SHELL_H__ */
