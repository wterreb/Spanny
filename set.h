
#ifndef __SETLIMITS_H__
#define __SETLIMITS_H__

  void settingsInit( void );
  void SET_RunCmd(  char *comand, char *args );
  void Details( void );
  void SetZoneSpeedLimits( char* param );
  void SetBuzzer (char* param );
  void SetSpeedUnit (char* param );
  void SetDefaultSettings();
  void SetAllDefaults();
  void showExistingSpeedLimits();
  void showExistingSettings();
  void showSpeedLimit(int zoneNr);
  int extract_params(char *buffer);
  void ShowSettings();

#endif //__SETLIMITS_H__
