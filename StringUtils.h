https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// Pre-compiler directive
#ifndef CONFIG_ACCESS_H
#define CONFIG_ACCESS_H

//header files
#include <stdio.h> // file opreations
#include <stdlib.h> // dynamic memory opreations

// create global constants - across files
typedef enum { False, True } Boolean;
typedef enum{ NO_ERR,
              INCOMPLETE_FILE_ERR,
              INPUT_BUFFER_OVERRUN_ERR } StringMainCode;

extern const int MAX_STR_LEN;
extern const int STD_STR_LEN;
extern const int SUBSTRING_NOT_FOUND;
extern const char SPACE;
extern const char NULL_CHAR;
extern const char SEMICOLON;
extern const char PERIOD;
extern const char LEFT_PAREN;
extern const char RIGHT_PAREN;
extern const int STR_EQ;
extern const char COLON;
extern const Boolean IGNORE_LEADING_WS;
extern const Boolean ACCEPT_LEADING_WS;

// function prototypes
int getStringLength( char *testStr );
void copyString( char *destinaton, char *source );
void concatenateString( char *destination, char *source );
int compareString( char *oneStr, char *otherStr );
void getSubString( char *destStr, char *sourceStr, 
                                     int starIndex, int endIndex );
int findSubString( char *testStr, char *searchSubStr );
void setStrToLowerCase( char *destStr, char *sourceStr );
char setCharToLowerCase( char testChar );
int getLineTo( FILE *filePtr, int bufferSize, char stopChar,
                          char *buffer, Boolean omitLeadWhiteSpace );
Boolean isEndOfFile( FILE *filePtr );

#endif // CONFIG_ACCESS_H
