
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
  
private:
  int EEPROMUpdateSpeedLimit(const long startAddress, const speedlimit& value);
  int EEPROMReadSpeedLimit(const long startAddress,  speedlimit& value);
  int EEPROM_START_LOC = 0;
};
 

#endif
