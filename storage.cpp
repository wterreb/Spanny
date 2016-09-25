#include "Arduino.h"
#include "storage.h"
#include <EEPROM.h>
#include "common.h"
#include "EEPROMAnything.h"

Storage::Storage(void )
{
    readSpeedLimits();
    readSettings();
}

void Storage::readSpeedLimits() {
   int addr = EEPROM_SPEEDS_START_LOC;
   for (int i=0; i<gZoneCount; i++) {
      EEPROM_readAnything(addr, gSpeedLimits[i]);
      addr += addr + sizeof(Speedlimit_t);
   }
}

void Storage::saveSpeedLimits() {
   int addr = EEPROM_SPEEDS_START_LOC;
   for (int i=0; i<gZoneCount; i++) {
      EEPROM_writeAnything(addr, gSpeedLimits[i]);
      addr += addr + sizeof(Speedlimit_t);
   }
}

void Storage::saveSettings() {
   int addr = EEPROM_SETTINGS_START_LOC;
    EEPROM_writeAnything(addr, gSettings);
}

void Storage::readSettings() {
   int addr = EEPROM_SETTINGS_START_LOC;
    EEPROM_readAnything(addr, gSettings);
}

