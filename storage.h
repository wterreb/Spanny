
#ifndef __STORAGE_H__
#define __STORAGE_H__

#include <Arduino.h>


class storage
{
public:
  void readSpeedLimits();
  void saveSpeedLimits();

private:
  void EEPROMLoad();
  void EEPROMSave() ;
  void EEPROMUpdateInt(int p_address, int p_value);
  unsigned int EEPROMReadInt(int p_address);
  void EEPROMWritelong(int address, long value);
  long EEPROMReadlong(long address);
};
 


#endif
