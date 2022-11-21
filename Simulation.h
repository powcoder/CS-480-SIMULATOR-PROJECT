https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder

// header files
#include "StringUtils.h"
#include "MetaDataAccess.h"

// create global constants - across files
typedef enum { NEW,
               READY,
               RUNNING,
               WAITING,
               TERMINATED } CurrentState;

// config data structure
typedef struct ProcessCtrlBlock
   {
    int state;
    int totalRumTime;
    int countNumber;
    
    struct ProcessCtrlBlock *next;
   }ProcessCtrlBlock;

typedef struct StoreOutputString
   {
    char outputString[ 100 ];
    
    struct StoreOutputString *next;
   } StoreOutputString;

// function prototypes
void displaySimulation( OpCodeType *metaDataOpPtr, ConfigDataType *configDataPtr, int controlCode);
double addProcessTime( OpCodeType *localPtr, ConfigDataType *configData );
StoreOutputString *outPutManager( char *outputBuffer, int controlCode, StoreOutputString *localHeader );
StoreOutputString *addOutputStringNode( StoreOutputString *localPtr, StoreOutputString *newNode, char *outputBuffer );
void outputToFile( StoreOutputString *localHeader, ConfigDataType *configData );
void *threadRunTimer( void *time );
ProcessCtrlBlock *createPCBList( ProcessCtrlBlock *processHeader, OpCodeType *localPtr );
ProcessCtrlBlock *addPCBNode( ProcessCtrlBlock *localPtr, ProcessCtrlBlock *newNode );
ProcessCtrlBlock *getReadyState( ProcessCtrlBlock *processHeader );

