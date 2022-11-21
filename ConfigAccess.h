https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder

// header files
#include "StringUtils.h"

// gloable constants
   // Note: start at 3 so it does not compete with StrngManipCode values
typedef enum { CFG_FILE_ACCESS_ERR = 3,
               CFG_CORRUPT_DESCRIPTOR_ERR,
               CFG_DATA_OUT_OF_RANGE_ERR,
               CFG_CORRUPT_PROMPT_ERR,
               CFG_VERSION_CODE,
               CFG_MD_FILE_NAME_CODE,
               CFG_CPU_SCHED_CODE,
               CFG_QUANT_CYCLES_CODE,
               CFG_MEM_AVAILABLES_CODE,
               CFG_PROC_CYCLES_CODE,
               CFG_IO_CYCLES_CODE,
               CFG_LOG_TO_CODE,
               CFG_LOG_FILE_NAME_CODE } ConfigCOdeMessage;

typedef enum { CPU_SCHED_SJF_N_CODE,
               CPU_SCHED_SRTF_P_CODE,
               CPU_SCHED_FCFS_P_CODE,
               CPU_SCHED_RR_P_CODE,
               CPU_SCHED_FCFS_N_CODE,
               LOGTO_MONITOR_CODE,
               LOGTO_FILE_CODE,
               LOGTO_BOTH_CODE } ConfigDataCodes;

// config data structure
typedef struct
   {
    double version;
    char metaDataFileName[ 100 ];
    int cpuSchedCode;
    int quantumCycles;
    long memAvailable;
    int propcCycleRate;
    int ioCycleRate;
    int logToCode;
    char logToFileName[ 100 ];
   } ConfigDataType;

// function prototypes
int getConfigData( char *fileName, ConfigDataType **configData );
int getDataLineCode( char *dataBuffer );
ConfigDataCodes getCpuSchedCode( char *codeStr );
ConfigDataCodes getLogToCode( char *logToStr );
Boolean valueInRange( int lineCode, int intVal,
                         double doubleVal, char *stringVal, long longVal );
void configCodeToString( int code, char *outString );

void displayConfigData( ConfigDataType *configData );
void displayConfigError( int errCode );
void clearConfigData( ConfigDataType **configDataPtr );


