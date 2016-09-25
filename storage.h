
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <Arduino.h>
#include "shared.h"

class Storage
{
public:
  Storage();
  void readSpeedLimits();
  void saveSpeedLimits();
  void saveSettings();
  void readSettings(); 
  
private:
  //int EEPROMReadSpeedLimit(const long startAddress,  Speedlimit_t& value);
  int EEPROM_SETTINGS_START_LOC = 0;
  int EEPROM_SPEEDS_START_LOC = 20;
};
 

#endif
