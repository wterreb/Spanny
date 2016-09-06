#include "Arduino.h"
#include "shellutils.h"
#include <stdio.h>
#include <stdlib.h>




//-----------------------------------------------------------------------------------------------------------------
unsigned int SHELLUTILS_getUIntValue( char *args ) {
    char *temp;

    temp = strtok( args, " " );
    if ( temp ){
        return atoi( temp );
    }

    return 0;
}

long SHELLUTILS_getLongValue( char *args ) {
    char *temp;
    long retVal = 0;
    temp = strtok( args, " " );
    char *ptr;
    if ( temp ){
     retVal = strtoul(temp, &ptr, 10);
    }
    return retVal;
}


//-----------------------------------------------------------------------------------------------------------------
char *SHELLUTILS_getString( char *args ) {
    return strtok( args, " " );
}

//-----------------------------------------------------------------------------------------------------------------
void SHELLUTILS_RunCommand( char *command, char *args, shellType_t const *pInfo ) {
    int i;

    for ( i=0; i < pInfo->numFuncs; i++ ) {
        if ( 0 == strcmp( pInfo->pFuncs[ i ].name, command ) ) {
            pInfo->pFuncs[ i ].function( args );
            break;
        }
    }

    if ( i >= pInfo->numFuncs ) {
        Serial.println( "Command not found" );
        SHELLUTILS_RunCommand( "help", "", pInfo );
    }
}

//-----------------------------------------------------------------------------------------------------------------
void SHELLUTILS_SetValue( char* args, shellType_t const *pInfo ) {
    char *name = SHELLUTILS_getString( args );
    unsigned int value = SHELLUTILS_getUIntValue( NULL );
    bool success = true;
    int i;

    for ( i=0; i < pInfo->numVars; i++ ) {
        if ( 0 == strcmp( pInfo->pVars[ i ].name, name ) ) {
            pInfo->pVars[ i ].value = value;
            Serial.print( pInfo->pVars[ i ].name );
            Serial.print( "Set to " );
            Serial.println( pInfo->pVars[ i ].value );
            break;
        }
    }

    if ( i >= pInfo->numVars ) {
        Serial.println( "Name not found" );
    }
}

//-----------------------------------------------------------------------------------------------------------------
void SHELLUTILS_PrintVars( shellType_t const *pInfo ) {
    int i;

    if ( 0 == pInfo->numVars ) {
        Serial.println( "No Adjustable Variables");
        return;
    }

    Serial.println( "Variable Summary:");
    for ( i=0; i < pInfo->numVars; i++ ) {
        Serial.print( pInfo->pVars[ i ].name );
        Serial.print( " (" );
        Serial.print( pInfo->pVars[ i ].value );
        Serial.print( ")" );
        if ( 0!= strcmp( "", pInfo->pVars[ i ].description ) ) {
            Serial.print( " - " );
            Serial.println( pInfo->pVars[ i ].description );
        }
    }
}

//-----------------------------------------------------------------------------------------------------------------
void SHELLUTILS_PrintHelp( shellType_t const *pInfo ) {
    int i;

    Serial.println( "Command Summary:" );
    for ( i=0; i < pInfo->numFuncs; i++ ) {
        Serial.print( pInfo->pFuncs[ i ].name );
        Serial.print( "/t/t-/t");
        Serial.println( pInfo->pFuncs[ i ].description );
    }
}

//-----------------------------------------------------------------------------------------------------------------
void SHELLUTILS_Reset( shellType_t const *pInfo ) {
    for ( int i=0; i < pInfo->numVars; i++ ) {
        pInfo->pVars[ i ].value = pInfo->pDefaults[ i ];
    }

    SHELLUTILS_RunCommand( "vars", "", pInfo );
}

