https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder

// header files
#include <stdio.h> // for file access
#include "StringUtils.h"


// global constants

typedef enum { MD_FILE_ACCESS_ERR = 3,
               MD_CORRUPT_DESCRIPTION_ERR,
               OPCMD_ACCESS_ERR,
               CORRUPT_OPCMD_LETTER_ERR,
               CORRUPT_OPCMD_NAME_ERR,
               CORRUPT_OPCMD_VALUE_ERR,
               NUBALANCED_START_END_ERR,
               COMPLETE_OPCMD_FOUND_MSG,
               LAST_OPCMD_FOUND_MSG } OpCodeMessage;
       

// op code data structure
typedef struct OpCodeType
   {
    char opLtr;
    char opName[ 100 ]; // length of op name - 99 characters
    int opValue;

    struct OpCodeType *next;
   } OpCodeType;

// function prototypes
int getOpCodes( char *fileName, OpCodeType **opCodeDataHead );
void displayMetaData( OpCodeType *localPtr );
void displayMetaDataError( int code );
OpCodeType *clearMetaDataList( OpCodeType *localPtr );
int getOpCommand( FILE *filePtr, OpCodeType *inData );
int updateStartCount( int count, char *opString );
int updateEndCount( int count, char *opString );
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode );
Boolean checkOpString( char *testStr );
Boolean inDigit( char testChar );

