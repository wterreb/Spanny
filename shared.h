#ifndef __SHARED_H__
#define __SHARED_H__

typedef struct command {
    char *name;
    void ( *command )( char *, char * );
    char *description;
} command_t;

typedef struct speedlimit {  
   byte lowerLimit;
   byte upperLimit;
   byte delaySeconds;
};   



#endif // __SHARED_H__
