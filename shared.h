#ifndef __SHARED_H__
#define __SHARED_H__

typedef struct command {
    char *name;
    void ( *command )( char *, char * );
    char *description;
} command_t;


#endif __SHARED_H__
