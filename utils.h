
#ifndef __UTILS_H__
#define __UTILS_H__

#define ARRAY_LENGTH(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

// Lower case to make it seem like a function
#define PRINT_TEST_START UTILS_printStart( __FUNCTION__ );
#define PRINT_TEST_END UTILS_printEnd( __FUNCTION__ );

void UTILS_printStart( const char * function );
void UTILS_printEnd( const char * function );


// The maximum time delay before we should use delay() instead of delayMicroseconds()
// as specified by arduino in their description of delayMicroseconds();
static const unsigned int maxUsTimeDelay  = 16383;

#endif /* __UTILS_H__ */

