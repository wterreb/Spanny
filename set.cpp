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

int nrElements = 0;
int zone = 0;
extern Storage storage;
const char* DRAWLINE = "-----------------------------------";

static functions_t funcs[] = {
    { "help",      SHELL_COMMAND PrintHelp,             "This help" },
    { "zone",      SHELL_COMMAND  SetZoneSpeedLimits,   "zone <zone> <lowerSpeedTheshold> <upperSpeedTheshold> <delaySecs>" },
    { "buzzer",    SHELL_COMMAND  SetBuzzer,            "buzzer <parameter> <value>" },
    { "speed",     SHELL_COMMAND  SetSpeedUnit,         "speedunit <kmh> <mph>" },
    { "defaults",  SHELL_COMMAND  SetAllDefaults,       "Sets all settings to default values (USE WITH CARE!) " },
    { "show",      SHELL_COMMAND  ShowSettings,         "shows all configurable settings" },
    { "",          SHELL_COMMAND  ShowSettings,         ""}
};

SHELL_INCLUDE_AFTER_DEFINITIONS( TEST_NAME2 )


void SET_RunCmd( char *command, char *args ) {
    SHELLUTILS_RunCommand( command, args, &all );
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
              case 1 : gSpeedLimits[idx].lowerLimit = params[i]; break;
              case 2 : gSpeedLimits[idx].upperLimit = params[i]; break;
              case 3 : gSpeedLimits[idx].delaySeconds = params[i]; break;
          }
      }
      storage.saveSpeedLimits();
      showExistingSpeedLimits();
    }
    return wordcount;
}

void SetZoneSpeedLimits( char* param ) {
  
  int nrParams = extract_params(param);
  if ((nrParams > 2) && (nrParams !=  4))
  {
    Serial.println("Invalid parameters.");
    Serial.println("Example : 'set zone 1 50 60 10'");
    Serial.println("          To set speedlimit zone 1 to between 50 km/h and 60 km/h and 10 second delay");
  }
  else {
   if ( nrParams ==  1 ) {
      showExistingSpeedLimits();
   }   
  }
}

int extractParam(char *buffer)
{
  char parambuffer[20];
  // Ignore leading space
  while(isspace(*buffer)) buffer++;
  // Find space after first word
  while(!isspace(*buffer)) buffer++;
  // Ignore leading space
  while(isspace(*buffer)) buffer++;
  Serial.print("'");Serial.print(buffer);Serial.println("'");
  int returnVal = atoi(buffer);
  return returnVal;
}



int extract_buzzerparams(char *buffer) {                                    
    int count;
    int wordcount = 0;
    int i = 0;
    char ch;
    
    char params[4];
    bool valid = false;

    int param = extractParam(buffer);
    if (param > 0) {
      if (strstr(buffer, "ontime ")) {
         gSettings.onTime = param;
         valid = true;
      }
      if (strstr(buffer, "offtime ")) {
         gSettings.offTime = param;
         valid = true;
      }
      if (strstr(buffer, "repeats ")) {
         gSettings.repeats = param;
         valid = true;
      }
      if (strstr(buffer, "interval ")) {
         gSettings.interval = param;
         valid = true;
      }
    }  
    if (strstr(buffer, "show ")) {
       valid = true;
    }
    if (strstr(buffer, "defaults")) {
       SetDefaultSettings();
       valid = true;
    }
    if (strstr(buffer, "test")) {
        gBuzzOnce = true;
        valid = true;
    }
    if (valid) {
      storage.saveSettings();
      showExistingSettings(); 
    }
    else {
       Serial.println("Invalid parameters.");
       Serial.println("Examples : ");
       Serial.println("\tset buzzer ontime 100");
       Serial.println("\tset buzzer offtime 50");
       Serial.println("\tset buzzer repeats 1");
       Serial.println("\tset buzzer interval 200");
       Serial.println("\tset buzzer show");
       Serial.println("\tset buzzer defaults");
       Serial.println("\tset buzzer test");
    }
    
}        

void SetBuzzer (char* param ) {
  int nrParams = extract_buzzerparams(param);
}

void SetSpeedUnit (char* param ) {
  bool isValid = false;
  if (strstr(param, "kmh")) {
     gSettings.useMetric = true;
     isValid = true; 
  }
  if (strstr(param, "mph")) {
     gSettings.useMetric = false;
     isValid = true; 
  }
  if ( isValid == true ) {
      storage.saveSettings();
      showExistingSettings(); 
  }
  else {
    Serial.println("Invalid parameter");
    Serial.println("Valid choices are:");
    Serial.println("\tset speed kmh");
    Serial.println("\tset speed mph");
  }
}

void SetDefaultSettings() {
    gSettings.onTime = 100;
    gSettings.offTime = 50;
    gSettings.repeats = 1;
    gSettings.interval = 200;
    gSettings.useMetric = true;
    gSettings.timezone = 0;
}

void SetOneZone(char idx, char lowerlimit, char upperlimit, char delaySec)
{
   gSpeedLimits[idx].lowerLimit = lowerlimit;
   gSpeedLimits[idx].upperLimit = upperlimit;
   gSpeedLimits[idx].delaySeconds = delaySec;
}

void SetAllDefaults () {
    SetDefaultSettings();
    SetOneZone(0, 35, 45, 5);
    SetOneZone(1, 55, 65, 5);
    SetOneZone(2, 85, 95, 5);
    SetOneZone(3, 105, 110, 5);
    SetOneZone(4, 110, 150, 0);
    SetOneZone(5, 0, 0, 0);
    SetOneZone(6, 0, 0, 0);
    SetOneZone(7, 0, 0, 0);
    SetOneZone(8, 0, 0, 0);
    SetOneZone(9, 0, 0, 0);
    storage.saveSettings();
    storage.saveSpeedLimits();
    ShowSettings();
}

void printTimeZone2( void ) {
  Serial.print("GMT");
  if ( gSettings.timezone > 0 ) {
    Serial.print("+");
  }
  Serial.print(gSettings.timezone);
}

void showExistingSpeedLimits() {
   char buff[50];
   Serial.println(DRAWLINE);
   Serial.println("|      Current Speed Limits       |");
   Serial.println(DRAWLINE);
   Serial.println("| Zone |  Low   |  High  | Delay  |");
   for (int i=0; i<gZoneCount; i++) {
      sprintf (buff,"| % 2d   |  %03d   |  %03d   |  %03d   |", i, gSpeedLimits[i].lowerLimit, gSpeedLimits[i].upperLimit, gSpeedLimits[i].delaySeconds );
      Serial.println(buff);
   }
   Serial.println(DRAWLINE);
}


void showExistingSettings() {
   Serial.println(DRAWLINE);
   Serial.println("|         Current Settings        |");
   Serial.println(DRAWLINE);
   Serial.print("buzzer ontime\t: "); Serial.println(gSettings.onTime);
   Serial.print("buzzer offtime\t: "); Serial.println(gSettings.offTime);
   Serial.print("buzzer repeats\t: "); Serial.println(gSettings.repeats);
   Serial.print("buzzer interval\t: "); Serial.println(gSettings.interval);
   Serial.print("speed        \t: "); 
   if (gSettings.useMetric) {
      Serial.println("kmh");
   }
   else {
      Serial.println("mph");
   }
   Serial.print("timezone     \t: "); 
   printTimeZone2();
   Serial.println("");
}

void ShowSettings()
{
   showExistingSettings();
   showExistingSpeedLimits(); 
}

