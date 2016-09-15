#include "Arduino.h"
#include "set.h"
#include "utils.h"
#include "shellutils.h"
#include "common.h"

#define TEST_NAME2 SET
SHELL_INCLUDE_BEFORE_DEFINITIONS( TEST_NAME2 )

// No variables
static store_t vars[ 0 ] = { };
static const unsigned int defaults [ 0 ] = { };
int limits[3][4];
int zone = 0;

static functions_t funcs[] = {
    { "help",      SHELL_COMMAND PrintHelp,              "This help" },
    { "speedlimit",      SHELL_COMMAND SET_SpeedLimit,   "speedlimit <zone> <lowerSpeedTheshold> <lowerSpeedTheshold> <delaySecs>" },
    {}
};

SHELL_INCLUDE_AFTER_DEFINITIONS( TEST_NAME2 )

void SET_RunCmd( char *command, char *args ) {
    SHELLUTILS_RunCommand( command, args, &all );
}

void showSpeedLimit(int zoneNr) {
     
     Serial.print("speedZone="); Serial.print(zoneNr);
     Serial.print(" lowSpeed="); Serial.print(limits[zoneNr][1]);
     Serial.print(" highSpeed="); Serial.print(limits[zoneNr][2]);
     Serial.print(" delaySecs="); Serial.println(limits[zoneNr][3]);
}

void showExistingSpeedLimits() {
  Serial.println("Show Speed Limits");
  for (int i=0; i< 3; i++)
  {
      showSpeedLimit(i); 
  }
}

int extract_params(char *buffer) {                                    
    int count;
    int wordcount = 0;
    int i = 0;
    char ch;
    char parambuffer[20];

    for (count = 0; count < strlen(buffer); count ++){
        ch = buffer[count];
           
        if( isblank(ch) || ch == '\0' ) {                   // if the character is blank, or null byte add 1 to the wordcounter       
             parambuffer[i] = '\0';   
             i = 0; 
             if (wordcount == 0)
                 zone = atoi(parambuffer);
             limits[zone][wordcount] = atoi(parambuffer);
             wordcount += 1;
        }
        else {
          parambuffer[i++] = ch;
        }
        if (ch == 0x0D)
            break;
    }
    return wordcount;
}

void SET_SpeedLimit( char* param ) {
   int nrParams = extract_params(param);
  if ((nrParams > 0) && (nrParams !=  4))
  {
    Serial.println("Invalid parameters.");
    Serial.println("Example : 'set speedlimit 1 50 60 10'");
    Serial.println("          To set speedlimit zone 1 to between 50 km/h and 60 km/h and 10 second delay");
  }
  else {
   if ( nrParams ==  0 ) {
      showExistingSpeedLimits();
   }   
   else {
      showSpeedLimit(zone);
   }
  }

}
