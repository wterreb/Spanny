
#ifndef __SETLIMITS_H__
#define __SETLIMITS_H__

  void settingsInit( void );
  void SET_RunCmd(  char *comand, char *args );
  void Details( void );
  static void SpeedLimit( char* channel );   
  static void showExistingSpeedLimits();
  void showSpeedLimit(int zoneNr);
  int extract_params(char *buffer);
  void ReadEeprom();

#endif //__SETLIMITS_H__
