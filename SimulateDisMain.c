https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// header files
#include <stdio.h> 
#include "ConfigAccess.h"
#include "Simulation.h"

/*
Function Name: main
Algorithm: driver function to test config and metadata file 
           upload operation together
Precondition: none
Postcondition: return 0 on success
Expections: none
Notes: demonstrates use of combined files
*/
int main( int argc, char **argv)
   {
    // initialize function/variables
    int configAccessResult;
    char configFileName[ MAX_STR_LEN ];
    ConfigDataType *configDataPtr;
    int mdAccessResult;
    char mdFileName[ MAX_STR_LEN ];
    OpCodeType *mdData;
    Boolean isConfigUpload;
    Boolean isMetaDataUpload;
    
    // display title
       // function: printf
    printf( "\nSimulator Program\n" );
    printf( "==========================\n\n" );

    // check for not correct number of command line arguments (two)
    if( argc < 2)
       {
        // print missing command line argument errorint
        printf( "ERROR: Program requires file name for config file" );
        printf( "as command line argument\n" );
        printf( "Program Terminared\n" );

        // return non-normal program result
        return 1;
       }

    // get data from configuration file
       // function: copyString, getConfigData
    copyString( configFileName, argv[ 1 ] );
    configAccessResult = getConfigData( configFileName, &configDataPtr );

    // check for successful upload
    if( configAccessResult == NO_ERR )
       {
        // print the success upload configuration
           // function: prinf
        printf( "Uploading Configuration Files\n" );
        
        // set config upload flag to ture;
        isConfigUpload = True;
       }

    // otherwise, assume failed upload
    else
       {
        // display configuration upload error
           // function: displayConfigError
        displayConfigError( configAccessResult );
        
        // set config upload flag to false;
        isConfigUpload = False;
       }

    // get data from meta data file
       // function: copyString, getMetaData
    copyString( mdFileName, configDataPtr->metaDataFileName );
    mdAccessResult = getOpCodes( mdFileName, &mdData );

    // check for successful upload
    if( mdAccessResult == NO_ERR )
       {
        // print the success meta data
           // function: prinf
        printf( "Uploading Meta Data Files\n" );
        
        // set meta data upload flag to ture
        isMetaDataUpload = True;
       }

    // otherwise, assume unsuccessful upload
    else
       {
        // display meta data error message 
           // displayMetaDataError
        displayMetaDataError( mdAccessResult );
        
        // set meta data upload flag to false
        isMetaDataUpload = False;
       }
    
    if( isConfigUpload && isMetaDataUpload )
       {
        // display simulation
           // function: displaySimulation
        displaySimulation( mdData, configDataPtr, configDataPtr->logToCode );
       }

       // shut down, clean up program
       // clear configuration data
          // function: clearConfigData
       clearConfigData( &configDataPtr );

       // clear meta data
          // function: clearMetaDataList
       mdData = clearMetaDataList( mdData );

       // add endline for vertical spacing
          // function: printf
       printf( "\n" );

       // return success
       return 0;
   }
