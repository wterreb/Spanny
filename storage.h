
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <Arduino.h>
#include "shared.h"

class storage
{
public:
  storage();
  void readSpeedLimits();
  void saveSpeedLimits();
  
private:
/*
  void EEPROMUpdateInt(int p_address, int p_value);
  unsigned int EEPROMReadInt(int p_address);
  void EEPROMWritelong(int address, long value);
  long EEPROMReadlong(long address);
  */
  int EEPROMUpdateSpeedLimit(const long startAddress, const speedlimit& value);
  int EEPROMReadSpeedLimit(const long startAddress,  speedlimit& value);
  int EEPROM_START_LOC = 0;
  int nrElements;
};
 

#endif
