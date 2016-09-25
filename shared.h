#ifndef __SHARED_H__
#define __SHARED_H__

typedef struct command {
    char *name;
    void ( *command )( char *, char * );
    char *description;
} command_t;

typedef struct Speedlimit_t {  
   byte lowerLimit;
   byte upperLimit;
   byte delaySeconds;
};  

typedef struct Settings_t {  
   int onTime;
   int offTime;
   int repeats;
   int interval;
   byte useMetric;
   int8_t timezone;
};   



#endif // __SHARED_H__
