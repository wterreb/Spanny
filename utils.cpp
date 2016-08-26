#include "Arduino.h"


//-----------------------------------------------------------------------------------------------------------------
void UTILS_printStart( const char * function ) {
    Serial.print( "START " );
    Serial.println( function );
}

//-----------------------------------------------------------------------------------------------------------------
void UTILS_printEnd( const char * function ) {
    Serial.print( "END " );
    Serial.println( function );
}

