#include "Arduino.h"
#include "set.h"
#include "utils.h"
#include "shellutils.h"
#include "common.h"
#include "shared.h"
#include "storage.h"

#define TEST_NAME2 SET
SHELL_INCLUDE_BEFORE_DEFINITIONS( TEST_NAME2 )

// No variables
static store_t vars[ 0 ] = { };
static const unsigned int defaults [ 0 ] = { };
//int limits[3][4];
//const int maxNumSpeedLimits = 10;
speedlimit speedLimits[10];
int nrElements = 0;
int zone = 0;
extern storage eeprom;

static functions_t funcs[] = {
    { "help",      SHELL_COMMAND PrintHelp,              "This help" },
    { "limits",    SHELL_COMMAND  SpeedLimit,   "limits <zone> <lowerSpeedTheshold> <upperSpeedTheshold> <delaySecs>" },
    { "read",      SHELL_COMMAND  ReadEeprom,     "shows contents of eeprom" },
    {}
};

SHELL_INCLUDE_AFTER_DEFINITIONS( TEST_NAME2 )

int getNrElemens() {
  return (sizeof(speedLimits)) / (sizeof(speedLimits[0])); 
}

void SET_RunCmd( char *command, char *args ) {
    SHELLUTILS_RunCommand( command, args, &all );
}


void showExistingSpeedLimits() {
   char buff[50];
   Serial.println("--------------------------------");
   Serial.println("|         Speed Limits          |");
   Serial.println("--------------------------------");
   Serial.println("| Zone |  Low  |  High | Delay |");
   int nr = getNrElemens();
   for (int i=0; i<nr; i++) {
      sprintf (buff,"| %02d   |  %02d   |  %02d   |  %02d   |", i, speedLimits[i].lowerLimit, speedLimits[i].upperLimit, speedLimits[i].delaySeconds );
      Serial.println(buff);
   }
   Serial.println("--------------------------------");
}

int extract_params(char *buffer) {                                    
    int count;
    int wordcount = 0;
    int i = 0;
    char ch;
    char parambuffer[20];
    char params[4];


    for (count = 0; count < strlen(buffer); count ++){
        ch = buffer[count];     
        if( isblank(ch) || ch == '\0' ) {                   // if the character is blank, or null byte add 1 to the wordcounter       
             parambuffer[i] = '\0';   
             i = 0; 
             if (wordcount == 0)
                 zone = atoi(parambuffer);
             params[wordcount] = atoi(parambuffer);
             wordcount += 1;
        }
        else {
          parambuffer[i++] = ch;
        }
        if (ch == 0x0D)
            break;
    }

    if (wordcount == 4) {
      int idx = 0;
      for (int i=0; i<sizeof(params); i++) {
          switch (i) {
              case 0:  idx = params[i];
              case 1 : speedLimits[idx].lowerLimit = params[i]; break;
              case 2 : speedLimits[idx].upperLimit = params[i]; break;
              case 3 : speedLimits[idx].delaySeconds = params[i]; break;
          }
      }
      eeprom.saveSpeedLimits();
      showExistingSpeedLimits();
    }
    return wordcount;
}

static void SpeedLimit( char* param ) {
  
  int nrParams = extract_params(param);
  if ((nrParams > 2) && (nrParams !=  4))
  {
    Serial.println("Invalid parameters.");
    Serial.println("Example : 'set speedlimit 1 50 60 10'");
    Serial.println("          To set speedlimit zone 1 to between 50 km/h and 60 km/h and 10 second delay");
  }
  else {
   if ( nrParams ==  1 ) {
      showExistingSpeedLimits();
   }   
  }

}

void ReadEeprom()
{
   eeprom.readSpeedLimits();
   showExistingSpeedLimits();
}

