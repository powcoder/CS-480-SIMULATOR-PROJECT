https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// header files
#include "StringUtils.h"
#include "ConfigAccess.h"
#include "Simulation.h"
#include "Simtimer.h"
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

/*
Funciton name: displaySimulation
Algorithm: simulate the whole process, when we first get A(start) step, 
           create PCB list, otherwise calculate the time. in I/O step, 
           create the thread. in A(end) step, free the PCB list. at the 
           end, if not just output to monitor, log string output list 
           to file.
Precondition: none
Postcondition: none
Exceptions: none
Notes: none
*/
void displaySimulation( OpCodeType *metaDataOpPtr, ConfigDataType *configDataPtr,
                           int controlCode )
   {
    // initialize local header to null
    StoreOutputString *localHeaderPtr = NULL;

    // initialize PCB header to null
    ProcessCtrlBlock *processHeaderPtr = NULL;

    //initialize other function/variables
    ProcessCtrlBlock *tempPCBPointer;
    char timeStr[ 9 ];
    double totalTime = 0;
    double stepTime;
    char outputString[ 100 ];
    pthread_t thread;

    // display title
       // function: sprintf
    sprintf( outputString, "\n================\n" );

    // manager the out put, include printf or create linked list
    localHeaderPtr = outPutManager( outputString, controlCode, localHeaderPtr );

    sprintf( outputString, "begin simulation\n" );

    // manager the out put, include printf or create linked list
    localHeaderPtr = outPutManager( outputString, controlCode, localHeaderPtr );

    // loop to the end of linked list
    while( metaDataOpPtr != NULL )
       {
        // check for S(start)
        if( metaDataOpPtr->opLtr == 'S' &&
               compareString( metaDataOpPtr->opName, "start" ) == 0 )
           {
            // set time to zero
               // function: accessTimer
            accessTimer( ZERO_TIMER, timeStr );
            
            // save system start string to buffer
               // function: sprintf
            sprintf( outputString, "%s, OS: System Start\n", timeStr );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // move to next meta data list node
            metaDataOpPtr = metaDataOpPtr->next;
           }
 
        // check for A(start)
        if( metaDataOpPtr->opLtr == 'A' &&
                compareString( metaDataOpPtr->opName, "start" ) == 0 )
           {
            // check for no PCB list
            if( processHeaderPtr == NULL )
               {
                // lap the time for success create PCB
                   // function: accessTimer
                accessTimer( LAP_TIMER, timeStr );

                // save create process string to the buffer
                   // function: sprintf
                sprintf( outputString, "%s, OS: Create Process Control Block\n", 
                            timeStr );

                // manager the out put, include printf or create linked list
                localHeaderPtr = outPutManager( outputString, controlCode, 
                                                   localHeaderPtr );

                // create PCB list and initialized all process in new state
                   // function: createPCBList
                processHeaderPtr = createPCBList( processHeaderPtr, 
                                                     metaDataOpPtr );

                // lap the time for success initialized the process in New state
                   // function: accessTime
                accessTimer( LAP_TIMER, timeStr );
           
                // save initialized process sting to buffer
                   // function: sprintf
                sprintf( outputString, "%s, OS: All processes initialized in New state\n", 
                            timeStr );

                // manager the out put, include printf or create linked list
                localHeaderPtr = outPutManager( outputString, controlCode, 
                                                   localHeaderPtr );

                // initialized the process in ready
                   // function: getReadyState
                processHeaderPtr = getReadyState( processHeaderPtr );
 
                // lap the time for success initialized the process in Ready state
                   // function: accessTimer
                accessTimer( LAP_TIMER, timeStr );
           
                // save process in ready state string to buffer
                   // function: sprintf
                sprintf( outputString, "%s, OS: All processes now in  Ready state\n", 
                            timeStr );

                // manager the out put, include printf or create linked list
                localHeaderPtr = outPutManager( outputString, controlCode, 
                                                   localHeaderPtr );

                // set temp PCB pointer to the header
                tempPCBPointer = processHeaderPtr;
               }

            // loop the linked list to A(end), calculate the whole time
               // function: addProcessTime
            totalTime = addProcessTime( metaDataOpPtr->next, configDataPtr );

            // lap the time for success select reamining time
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr ); 

            // save success select reamining time string to buffer
               // function: sprintf
            sprintf( outputString, "%s, OS: Process %d selected with %lg ms remaining\n", 
                        timeStr, tempPCBPointer->countNumber, totalTime ); 

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // initialized the process in running
            tempPCBPointer->state = RUNNING; 

            // lap the time for success initialized the process in running
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr ); 
 
            // save success initialized the process in running string to buffer
               // function: sprintf
            sprintf( outputString, "%s, Process %d set in RUNNING state\n\n", timeStr, 
                        tempPCBPointer->countNumber );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // move to next meta data list node
            metaDataOpPtr = metaDataOpPtr->next;
           }
        
        // check for P
        if( metaDataOpPtr->opLtr == 'P' )
           {
            // lap the time for run operation start
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );
     
            // get the value from store step time linked list
            stepTime = metaDataOpPtr->opValue * configDataPtr->propcCycleRate;

            //save time for run operation start string to buffer
               // function: sprintf
            sprintf( outputString, "%s, %s operation start\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // simulate run operation
            runTimer( stepTime );
 
            // lap the time for run operation end
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );

            // save time for run operation end string to buffer
               // function: printf
            sprintf( outputString, "%s, %s operation end\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // move to next node
            metaDataOpPtr = metaDataOpPtr->next;
           }
       
        // check for I
        if( metaDataOpPtr->opLtr == 'I' )
           {
            // lap the time for run operation start
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );
     
            // get the value from store step time linked list
            stepTime = metaDataOpPtr->opValue * configDataPtr->ioCycleRate;

            // save time for run operation start string to buffer
               // function: sprintf
            sprintf( outputString, "%s, %s input start\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // set process to waiting state
            tempPCBPointer->state = WAITING;

            // create a thread
            pthread_create( &thread, NULL, threadRunTimer, &stepTime );

            // wait thread terminate
            pthread_join( thread, NULL );
 
            // lap the time for run operation end
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );

            // save time for run operation end string to buffer
               // function: sprintf
            sprintf( outputString, "%s, %s input end\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr);

            // set process to ready state
            tempPCBPointer->state = READY;

            // set process to running state
            tempPCBPointer->state = RUNNING; 

            // move to next node
            metaDataOpPtr = metaDataOpPtr->next;
           }

        // check for O
        if( metaDataOpPtr->opLtr == 'O' )
           {
            // lap the time for run operation start
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );
     
            // get the value from store step time linked list
            stepTime = metaDataOpPtr->opValue * configDataPtr->ioCycleRate;

            // save time for run operation start string to buffer
               // function: sprintf
            sprintf( outputString, "%s, %s output start\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // set process to waiting state
            tempPCBPointer->state = WAITING;

            // create a thread
            pthread_create( &thread, NULL, threadRunTimer, &stepTime );

            // wait thread terminate
            pthread_join( thread, NULL );
 
            // lap the time for run operation end
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );

            // save time for run operation end string to buffer
               // function: sprintf
            sprintf( outputString, "%s, %s output end\n", timeStr, 
                        metaDataOpPtr->opName );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // set process to ready state
            tempPCBPointer->state = READY;

            // set process to running state
            tempPCBPointer->state = RUNNING; 

            // move to next node
            metaDataOpPtr = metaDataOpPtr->next;
           }

        // check for A(end)
        if( metaDataOpPtr->opLtr == 'A' &&
               compareString( metaDataOpPtr->opName, "end" ) == 0 )
           {
            // initialized all process in exit
            tempPCBPointer->state = TERMINATED; 

            // lap the time for success initialized the process in exit
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr ); 

            // save success initialized the process in exit string to buffer
               // function: sprintf
            sprintf( outputString, "\n%s, Process %d ended and set in EXIT state\n\n", 
                        timeStr, tempPCBPointer->countNumber );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // move to next meta data list node
            metaDataOpPtr = metaDataOpPtr->next;

            // move to next PCB node
            tempPCBPointer = tempPCBPointer->next;
           }
 
        // check for S(end)
        if( metaDataOpPtr->opLtr == 'S' &&
               compareString( metaDataOpPtr->opName, "end" ) == 0 )
           {
            // lap the time for stop
               // function: accessTimer
            accessTimer( LAP_TIMER, timeStr );
            
            // save system stop string to buffer
               // function: sprintf
            sprintf( outputString, "%s, System stop\n", timeStr );

            // manager the out put, include printf or create linked list
            localHeaderPtr = outPutManager( outputString, controlCode, 
                                               localHeaderPtr );

            // stop system
               // function: accessTimer
            accessTimer( STOP_TIMER, timeStr );
       
            // move to next meta data list node
            metaDataOpPtr = metaDataOpPtr->next;

            // free the PCB list
               // function: free
            if( processHeaderPtr != NULL )
               {
                free( processHeaderPtr );
               }

           }
   
       }
    
     // print end simulation
        // function: sprintf
     sprintf( outputString, "\nEnd Simulation - Complete\n" );

     // manager the out put, include printf or create linked list
     localHeaderPtr = outPutManager( outputString, controlCode, 
                                        localHeaderPtr );

     sprintf( outputString, "\n=========================\n" );

     // manager the out put, include printf or create linked list
     localHeaderPtr = outPutManager( outputString, controlCode, 
                                        localHeaderPtr );

     // check for log to file or both
     if( controlCode != LOGTO_MONITOR_CODE )
        {
         // print to the file
            // function: outputToFile
         outputToFile( localHeaderPtr, configDataPtr );

         printf( "\n=========================\n" );
         printf( "\nsuccessful log to file\n" );
        }

     // free the output list
        // function: free
     if( localHeaderPtr != NULL )
        {
         free( localHeaderPtr );
        }

   }

/*
Function Name: getReadyState
Algorithm: get all PCB node state to ready
Precondition: none
Postcondition: return the PCB node state header
Expections: none
Notes: none
*/
ProcessCtrlBlock *getReadyState( ProcessCtrlBlock *processHeader )
   {
    // initialize function/variables
    ProcessCtrlBlock *tempPointer;
  
    // set the pointer to the header
    tempPointer = processHeader;

    // loop to the end of list
    if( tempPointer == NULL )
       {
        // change the state to ready
        tempPointer->state = READY;

        // move to next node
        tempPointer = tempPointer->next;
       }

    // return the PCB list header
    return processHeader;
   }

/*
Function Name: createPCBList
Algorithm: create PCB list
Precondition: none
Postcondition: return the PCB node state header
Expections: none
Notes: none
*/
ProcessCtrlBlock *createPCBList( ProcessCtrlBlock *processHeader, 
                                    OpCodeType *localPtr )
   {
    // initialize function/variables
    ProcessCtrlBlock *newNodePtr;
    int countNumber = 0;

    // loop the local linked list
    while( localPtr != NULL )
       {
        // check for A( start )
        if( localPtr->opLtr == 'A' &&
                compareString( localPtr->opName, "start" ) == 0 )
           {
            // allocate memory for the temporary data structure
               // function : malloc
            newNodePtr = ( ProcessCtrlBlock * ) malloc( sizeof( ProcessCtrlBlock ) );  
   
            // initialized the process in New state
            newNodePtr->state = NEW; 
        
            // initialized the process counter
            newNodePtr->countNumber = countNumber; 

            // create PCB linked list
            processHeader = addPCBNode( processHeader, newNodePtr );

            // add the counter
            countNumber++;

            // move to next node
            localPtr = localPtr->next;

            // release memory to OS
              // function : free
            free( newNodePtr );
           }

        else
           {
            // move to next node
            localPtr = localPtr->next;
           }
       }

    // return the PCB list header
    return processHeader;
   }

/*
Function Name: addPCBNode
Algorithm: add PCB node to the PCB list
Precondition: none
Postcondition: return the PCB node state header
Expections: none
Notes: none
*/
ProcessCtrlBlock *addPCBNode( ProcessCtrlBlock *localPtr, 
                                 ProcessCtrlBlock *newNode )
   {
    //check for loacl pointer assigned to null
    if( localPtr == NULL )
       {
        // access memory for new Link/node
           // function: malloc
        localPtr = ( ProcessCtrlBlock * ) malloc( sizeof( ProcessCtrlBlock ) );

        // assign value to newly created node
        // assign next poiter to null
        localPtr->countNumber = newNode->countNumber;
        localPtr->state = newNode->state;
        localPtr->next = NULL;

        // return current local pointer
        return localPtr;
       }

    // assume end of list not found yet
    // assign recursive function to current's next link
       // function: addNewNode
    localPtr->next = addPCBNode( localPtr->next, newNode );

    //return current local pinter
    return localPtr;
   }

/*
Function Name: threadRunTimer
Algorithm: do run time method in thread
Precondition: none
Postcondition: return none pointer
Expections: none
Notes: none
*/
void *threadRunTimer( void *time )
   {
    // initialize function/variables
    double stepTime = *(double *)time;
    
    // simulation input or output step
       // function: runTimer
    runTimer( stepTime );

    // destory the thread
       // function: pthread_exit
    pthread_exit( 0 );

    // return void
    return ((void *)0);
   }

/*
Function Name: addProcessTime
Algorithm: go through all the list and addeach time to calculate the 
           whole time
Precondition: none
Postcondition: reutrn the while time
Expections: none
Notes: none
*/
double addProcessTime( OpCodeType *localPtr, ConfigDataType *configData )
   {
    // initialize function/variables
    double totalTime = 0;

    // loop the linked list, until A(end)0
    while( localPtr->opLtr != 'A' 
              && compareString( localPtr->opName, "end" ) != 0 )
       {
        if( localPtr->opLtr == 'P' )
           {
            // calculate the run time
            totalTime += configData->propcCycleRate * localPtr->opValue;

       
            // move to next meta data list node
            localPtr = localPtr->next;
           }
      
        if( localPtr->opLtr == 'I'
               || localPtr->opLtr == 'O' )
           {
            // calculate the run time
            totalTime += configData->ioCycleRate * localPtr->opValue;

            // move to next meta data list node
            localPtr = localPtr->next;
           }
       }
    
    // return the local header
    return totalTime;
   }

/*
Function Name: outPutManager
Algorithm: if monitor, just printf. if file, 
           create the new list and save buffr
           in the list. is both, do both
Precondition: none
Postcondition: reutrn the list header
Expections: none
Notes: none
*/
StoreOutputString *outPutManager( char *outputBuffer, int controlCode, 
                                     StoreOutputString *localHeader )
   {
    // initialize function/variables
    StoreOutputString *newNodePtr;

    // check for mointor only
    if( controlCode == LOGTO_MONITOR_CODE )
       {
        // printf the buffer
        printf( outputBuffer );
       }

    // check for file only
    else if( controlCode == LOGTO_FILE_CODE )
       {
        // allocate memory for the temporary data structure
           // function : malloc
        newNodePtr = ( StoreOutputString * ) malloc( sizeof( StoreOutputString ) ); 

        // add the node to linked list
           // function : addOutputStringNode
        localHeader = addOutputStringNode( localHeader, newNodePtr, outputBuffer );
 
        // release memory to OS
           // function : free
        free( newNodePtr );
       }

    // check for both
    else
       {
        // printf the buffer
        printf( outputBuffer );

        // allocate memory for the temporary data structure
           // function : malloc
        newNodePtr = ( StoreOutputString * ) malloc( sizeof( StoreOutputString ) ); 

        // add the node to linked list
           // function : addOutputStringNode
        localHeader = addOutputStringNode( localHeader, newNodePtr, outputBuffer );
 
        // release memory to OS
           // function : free
        free( newNodePtr );
       }

    // retun the localHeader
    return localHeader;
   }

/*
Function Name: addOutputStringNode
Algorithm: add the node to the list
Precondition: none
Postcondition: reutrn the list header
Expections: none
Notes: none
*/
StoreOutputString *addOutputStringNode( StoreOutputString *localPtr, 
                                        StoreOutputString *newNode, char *outputBuffer )
   {
    //check for loacl pointer assigned to null
    if( localPtr == NULL )
       {
        // set out put buffer to the node
           // function: copyString
        copyString( newNode->outputString, outputBuffer );

        // access memory for new Link/node
           // function: malloc
        localPtr = ( StoreOutputString * ) malloc( sizeof( StoreOutputString ) );

        // assign value to newly created node
        // assign next poiter to null
           // function: copyString
        copyString( localPtr->outputString, newNode->outputString );
        localPtr->next = NULL;

        // return current local pointer
        return localPtr;
       }

    // assume end of list not found yet
    // assign recursive function to current's next link
       // function: addNewNode
    localPtr->next = addOutputStringNode( localPtr->next, newNode, 
                                             outputBuffer );

    //return current local pinter
    return localPtr;
   }

/*
Function Name: outputToFile
Algorithm: if monitor, out put the buffer to the file
Precondition: none
Postcondition: none
Expections: none
Notes: none
*/
void outputToFile( StoreOutputString *localHeader, ConfigDataType *configData )
   {
    // initialize function/variables
    char displayString[ STD_STR_LEN ];
    StoreOutputString *tempHeader;
    const char WRITE_FLAG[] = "w+";

    // create a file poiner
    FILE *newFile;

    // use file path to reate and open the file
    newFile = fopen( configData->logToFileName, WRITE_FLAG ); 

    // put the temp header to local header
    tempHeader = localHeader;

    // print the header
       // function: printf
    fprintf( newFile, "=========================\n" );
    fprintf( newFile, "Simulator Log File Header\n\n" );

    // prinf the Simulator Log File
       // function: printf,configCodeToString;
    fprintf( newFile, "Program File name       : %s\n", configData->metaDataFileName );
    configCodeToString( configData->cpuSchedCode, displayString );
    fprintf( newFile, "CPU schedule selection  : %s\n", displayString );
    fprintf( newFile, "Quantum time            : %d\n", configData->quantumCycles );
    fprintf( newFile, "Memory Avaliable        : %ld\n", configData->memAvailable );
    fprintf( newFile, "Process cycle rate      : %d\n", configData->propcCycleRate );
    fprintf( newFile, "I/O cycle rate          : %d\n", configData->ioCycleRate );
    configCodeToString( configData->logToCode, displayString );

    // loop to the end of linked list
    while( tempHeader != NULL )
       {
        // print the output buffer to the file
           // function: printf
        fprintf( newFile, tempHeader->outputString );

        // move to next node
        tempHeader = tempHeader->next;
       }
       // end loop
   }














