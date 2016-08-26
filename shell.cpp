#include "Arduino.h"

#include "utils.h"
#include "shell.h"
#include "shared.h"
#include "gps.h"

static const char ASCII_BELL = 0x07;
static const char ASCII_DEL  = 0x08;
static const char ASCII_CR   = 0x0D;

static char serialLineBuffer[ LINE_BUFFER_SIZE ];
static char serialLineBufferCopy[ LINE_BUFFER_SIZE ];
static unsigned int serialPosition = 0;




static void printHelp ( char *, char * );

command_t availableCommands[] = {
    { "help",      printHelp,               "This command" },
    { "gps,        GPS_RunCmd,     "GPS related"}
    { "set",       SETTINGS_Set,        "CI210 tests: Immunity from Continuous PowerLine Disturbances" },
    { "fake",      FAKE_fake,        "CI260 tests: Immunity to Voltage Dropout" },
    {} 
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
        Serial.println( "Unknown command" );
    }
    printPrompt();
}

//-----------------------------------------------------------------------------------------------------------------
void SHELL_printHelp ( void ) {
    printHelp( "", "" );
};

//-----------------------------------------------------------------------------------------------------------------
void SHELL_process( void ) {
    if (Serial.available() > 0)
    {
        int byteReceived = Serial.read();

        switch ( byteReceived ) {
            case ASCII_DEL:  // Backspace
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
                serialLineBuffer[ serialPosition ] = 0;
                SHELL_processLine( (char *)&serialLineBuffer );
                mempcpy( serialLineBufferCopy, serialLineBuffer, LINE_BUFFER_SIZE );
                serialPosition = 0;
                break;

            case '!':
                // Repeat last line
                if ( 0 == serialPosition ) {
                    mempcpy( serialLineBuffer, serialLineBufferCopy, LINE_BUFFER_SIZE );
                    SHELL_processLine( (char *)&serialLineBuffer );
                }
                break;

            default:
                if ( serialPosition < LINE_BUFFER_SIZE ) {
                    serialLineBuffer[ serialPosition ] = (char)byteReceived;
                    serialPosition++;
                    Serial.write( byteReceived );
                }
                else {
                    Serial.write( ASCII_BELL );
                }
                break;
        }
    }
}
