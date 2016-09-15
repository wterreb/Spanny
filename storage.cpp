#include "Arduino.h"
#include "storage.h"
#include <EEPROM.h>



void storage::readSpeedLimits()
{

  
}

void storage::EEPROMLoad() {
   int addr = 0;
   contrast = EEPROM.read(addr++);
   for (int i=0; i<6; i++) {
      addr += i*2;
      speedlimit[i] = EEPROMReadInt(addr);
   }
   addr += 2;
   odoDistance = EEPROMReadlong( addr );
}

void storage::EEPROMSave() {
   int addr = 0;
   EEPROM.update(addr++, contrast);
   for (int i=0; i<6; i++) {
      addr += i*2;
      EEPROMUpdateInt(addr, speedlimit[i]);
   }
   addr += 2;
   EEPROMWritelong( addr, odoDistance );
}
*/

//This function will write a 2 byte integer to the eeprom at the specified address and address + 1
void storage::EEPROMUpdateInt(int p_address, int p_value) {
     byte lowByte = ((p_value >> 0) & 0xFF);
     byte highByte = ((p_value >> 8) & 0xFF);

#if defined(__SAM3X8E__)
  // do nothing forDue's SAM3XA 
#else
     EEPROM.update(p_address, lowByte);
     EEPROM.update(p_address + 1, highByte);
#endif

}

//This function will read a 2 byte integer from the eeprom at the specified address and address + 1
unsigned int storage::EEPROMReadInt(int p_address) {
  #if defined(__SAM3X8E__)
    // do nothing for Due's SAM3XA 
  #else
     byte lowByte = EEPROM.read(p_address);
     byte highByte = EEPROM.read(p_address + 1);

     return ((lowByte << 0) & 0xFF) + ((highByte << 8) & 0xFF00);
  #endif    
  
}

//This function will write a 4 byte (32bit) long to the eeprom at
//the specified address to address + 3.
void storage::EEPROMWritelong(int address, long value) {
      //Decomposition from a long to 4 bytes by using bitshift.
      //One = Most significant -> Four = Least significant byte
      char four = (value & 0xFF);
      char three = ((value >> 8) & 0xFF);
      char two = ((value >> 16) & 0xFF);
      char one = ((value >> 24) & 0xFF);
#if defined(__SAM3X8E__)
  // do nothing forDue's SAM3XA 
#else
      //Write the 4 bytes into the eeprom memory.
      EEPROM.update(address, four);
      EEPROM.update(address + 1, three);
      EEPROM.update(address + 2, two);
      EEPROM.update(address + 3, one);
#endif      
}

long storage::EEPROMReadlong(long address) {
  #if defined(__SAM3X8E__)
  // do nothing forDue's SAM3XA 
  return 0;
  #else
      //Read the 4 bytes from the eeprom memory.
      long four = EEPROM.read(address);
      long three = EEPROM.read(address + 1);
      long two = EEPROM.read(address + 2);
      long one = EEPROM.read(address + 3);

      //Return the recomposed long by using bitshift.
      return ((four << 0) & 0xFF) + ((three << 8) & 0xFFFF) + ((two << 16) & 0xFFFFFF) + ((one << 24) & 0xFFFFFFFF); 
  #endif       
}
