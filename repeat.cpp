#include "Arduino.h"
#include "utils.h"
#include "shellutils.h"
#include "shell.h"
#include "output.h"
#include "killit.h"

#define TEST_NAME REPEAT
SHELL_INCLUDE_BEFORE_DEFINITIONS( TEST_NAME )

typedef enum varType {
    MAX_ENUM  // Always last
} varType_t;

static store_t vars[ MAX_ENUM ] = {
};

static const unsigned int defaults [ ARRAY_LENGTH( vars ) ] = {
};

static functions_t funcs[] = {
};

SHELL_INCLUDE_AFTER_DEFINITIONS( TEST_NAME )

//-----------------------------------------------------------------------------------------------------------------
void REPEAT_RunCommand( char *command, char *args ) {
    unsigned int repeatNum = SHELLUTILS_getUIntValue( command );

    if ( 0==repeatNum ) {
        Serial.println( "Invalid repeat number" );
    }

    for ( int i=1; i<=repeatNum; i++ ) {
        Serial.print( "Repeat command #" );
        Serial.print( i );
        Serial.print( "/" );
        Serial.print( repeatNum );
        Serial.print( ": " );
        Serial.println( args );
        SHELL_processLine( args  );
    }

    Serial.println( "Repeat end" );
}


