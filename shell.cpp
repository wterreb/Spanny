#include "Arduino.h"

#include <string.h>
#include "utils.h"
#include "shell.h"
#include "shared.h"
#include "gps.h"

static const char ASCII_BELL = 0x07;
static const char ASCII_DEL  = 0x08;
static const char ASCII_CR   = 0x0D;
static const char ASCII_NL   = 0x0A;

static char serialLineBuffer[ LINE_BUFFER_SIZE ];
static char serialLineBufferCopy[ LINE_BUFFER_SIZE ];
static unsigned int serialPosition = 0;


static void printHelp ( char *, char * );

command_t availableCommands[] = {
    { "help",      printHelp,               "This command" },
    { "gps",       GPS_RunCmd,     "GPS related"},
    { "set",       SET_RunCmd,     "SET limits"},
 //   {} 
};


//-----------------------------------------------------------------------------------------------------------------
 static void printPrompt ( void ) {
    Serial.println( "" );
    Serial.print( ">" );
}

//-----------------------------------------------------------------------------------------------------------------
 static void printHelp ( char *, char * ) {
    Serial.println( "Spanny Help" );
    Serial.print( __TIME__ );
    Serial.print( " " );
    Serial.println( __DATE__ );
    Serial.println( "-----------------------------------------------------------" );
    Serial.println( "! - Repeat last line" );
    Serial.println( "Type help after any of the following commands for more information" );
    Serial.println( "" );

    for ( int i=0; i<ARRAY_LENGTH( availableCommands ); i++ ) {
        Serial.print( availableCommands[i].name );
        Serial.print( " - " );
        Serial.println( availableCommands[i].description );
    }
    printPrompt();
}

static const unsigned int maxSubCommandSize = 30;

//-----------------------------------------------------------------------------------------------------------------
void SHELL_processLine( char *line  ) {
    int i;
    char *start;
    char *command;
    char *ptr;
    char *arguments;
    char subCommand[ maxSubCommandSize ];
    char lineCopy[ LINE_BUFFER_SIZE ];
    memcpy( lineCopy, line, LINE_BUFFER_SIZE );

    if ( ( command = strtok( lineCopy, " " )) == NULL) {
        printPrompt();
        return;
    }
    start = (char *)&lineCopy;

    for ( i=0; i<ARRAY_LENGTH( availableCommands ); i++ ) {
        if ( 0==strcmp( availableCommands[ i ].name, command ) ) {

            // Determine what the next argument is
            ptr = strtok( NULL, " " );
            if ( ptr ) {
              strncpy( subCommand, ptr, maxSubCommandSize );
              subCommand[ maxSubCommandSize ] = 0;
            }

            // And a pointer to the variable list of arguments ( if any )
            arguments = strtok( NULL, " " );
            if ( arguments !=0 ) {
                // Pass the copy of serialLineBufferCopy, so we retain the original
                // in case it is needed later.
                memcpy( lineCopy, line, LINE_BUFFER_SIZE );
                arguments = &lineCopy[ arguments-start ];
            }
            availableCommands[ i ].command( (char *)&subCommand, arguments );
            break;
        }
    }

    if ( i >= ARRAY_LENGTH( availableCommands ) ) {
        Serial.print( "Unknown command : '" );
        Serial.print( line );
        Serial.println("'");
    }
    printPrompt();
}

//-----------------------------------------------------------------------------------------------------------------
void SHELL_printHelp ( void ) {
    printHelp( "", "" );
};

//-----------------------------------------------------------------------------------------------------------------
int SHELL_process( void ) {

    int byteReceived = 0;
    if (Serial.available() > 0)
    {
        byteReceived = Serial.read();
   
        switch ( byteReceived ) {
            case ASCII_DEL:  // Backspace
                Serial.print("<");
                // Delete last char
                if ( serialPosition > 0 ){
                    Serial.write( ASCII_DEL );
                    Serial.print( ' ' );
                    Serial.write( ASCII_DEL );
                    serialPosition--;
                }
                break;

            case ASCII_CR:
                // Process line
                Serial.println( "" );   
                serialLineBuffer[ serialPosition++ ] = ' ';
                serialLineBuffer[ serialPosition ] = 0;
                SHELL_processLine( (char *)&serialLineBuffer );
                memcpy( serialLineBufferCopy, serialLineBuffer, LINE_BUFFER_SIZE );
                memset(serialLineBuffer, 0, LINE_BUFFER_SIZE);
                serialPosition = 0;
                break;

            case ASCII_NL:
               // Ignore   
               break;

            case '!':
                // Repeat last line
                if ( 0 == serialPosition ) {
                    memcpy( serialLineBuffer, serialLineBufferCopy, LINE_BUFFER_SIZE );
                    SHELL_processLine( (char *)&serialLineBuffer );
                }
                break;

            default:
                if ( serialPosition < LINE_BUFFER_SIZE ) {
                    serialLineBuffer[ serialPosition ] = tolower((char)byteReceived);
                    serialPosition++;
                    Serial.write( byteReceived );
                }
                else {
                    Serial.write( ASCII_BELL );
                }
                break;
        }
    }
    return byteReceived;
}
