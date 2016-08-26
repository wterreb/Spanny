

#ifndef __SHELLUTILS_H__
#define __SHELLUTILS_H__


typedef struct functions {
    char *name;
    void ( *function )( char * );
    char *description;
} functions_t;

typedef struct store {
    unsigned int value;
    char *name;
    char *description;
} store_t;

typedef struct shellType {
    functions_t *pFuncs;
    unsigned int numFuncs;
    store_t *pVars;
    unsigned int *pDefaults;
    unsigned int numVars;
} shellType_t;

#define SHELL_COMMAND (void (*)(char*))

#define SHELL_INCLUDE_BEFORE_DEFINITIONS( name ) \
    static void PrintVars( void ); \
    static void PrintHelp( void ); \
    static void ResetDefaults( void ); \
    static void SetValue( char* args );

#define SHELL_INCLUDE_AFTER_DEFINITIONS( name ) \
    shellType_t const all = { .pFuncs = funcs, .numFuncs = ARRAY_LENGTH( funcs ), \
            .pVars = vars, .pDefaults = (unsigned int *)defaults, \
            .numVars = ARRAY_LENGTH( vars ) }; \
    static void PrintVars( void ) { SHELLUTILS_PrintVars( &all ); }   \
    static void PrintHelp( void ) { SHELLUTILS_PrintHelp( &all ); } \
    static void ResetDefaults( void ) { SHELLUTILS_Reset( &all ); } \
    static void SetValue( char* args ) { SHELLUTILS_SetValue( args, &all ); }

unsigned int SHELLUTILS_getUIntValue( char *args );
char *SHELLUTILS_getString( char *args );
void SHELLUTILS_RunCommand( char *command, char *args, shellType_t const *pInfo );
void SHELLUTILS_SetValue( char* args, shellType_t const *pInfo );
void SHELLUTILS_PrintVars( shellType_t const *pInfo );
void SHELLUTILS_PrintHelp( shellType_t const *pInfo );
void SHELLUTILS_Reset( shellType_t const *pInfo  );

#endif __SHELLUTILS_H__

