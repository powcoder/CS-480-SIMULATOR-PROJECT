https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
// header files
#include "MetaDataAccess.h"

/*
Function Name: getOpCodes
Algorithm: opens file, acquires Op Codes,
           returns pointer to head of linked list
Precondition: for correct operation, file is available, 
              is formatted correctly,
              and has all correctly formed op codes
Postcondition: in correct operation,
               returns pointer to head of op code linked list
Expections: correctly and appropriately respond to and reports file access 
            failure, incorrectly formatted lead or end descriptors,
            incorrectly formatted prompt, incorrect op code letter,
            incorrectly op code name, op code value out of range,
            and incomplete file conditions
Notes: none
*/
int getOpCodes( char *fileName, OpCodeType **opCodeDataHead )
   {
    // initialize function/varioubles

       // initialize strat only constat
       const char READ_ONLY_FLAG[] = "r";

       // initialize strat and end counters for balanced app operations
       int startCount = 0, endCount = 0;

       // initialize local header to null
       OpCodeType *localHeader = NULL;

       // initialize variables
       int accessResult;
       char dataBuffer[ MAX_STR_LEN ];
       OpCodeType *newNodePtr;
       FILE *fileAccessPtr;

    // initialize op code data pointer for balanced app operations
    *opCodeDataHead = NULL;

    // open file for reading
       // function: fopen
    fileAccessPtr = fopen( fileName, READ_ONLY_FLAG );

    // check for file open failure
    if( fileAccessPtr == NULL )
       {
        // return file access error
        return MD_FILE_ACCESS_ERR;
       }
    // check first line for correct leader
       // function: getLineTo, compareString
    if( getLineTo( fileAccessPtr, MAX_STR_LEN, COLON,
                      dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
       || compareString( dataBuffer, "Start Program Meta-Data Code" ) != STR_EQ )
       {
        //close file
           //function: fclose
        fclose( fileAccessPtr );

        //return corrupt descriptor error
        return MD_CORRUPT_DESCRIPTION_ERR;
       }

    // allocate memory for the temporary data structure
       // function : malloc
    newNodePtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

    // get to the first op command
       // function: getOpCommand
    accessResult = getOpCommand( fileAccessPtr, newNodePtr );

    // get start and end counts for latter comparsion
       // function: updateStartCount, updateEndCount
    startCount = updateStartCount( startCount, newNodePtr->opName );
    endCount = updateStartCount( endCount, newNodePtr->opName );

    // check for failure of first complete op command
    if( accessResult != COMPLETE_OPCMD_FOUND_MSG )
       {
        // close file
           // function: fclose
        fclose( fileAccessPtr );

        // clear data from the structure list
           // function: clearMetaDataList
        *opCodeDataHead = clearMetaDataList( localHeader );

        // free temporary structure memory
           // function: free
        free( newNodePtr );

        // return result of opreation
        return accessResult;
       }

    // loop across all remaining op commands
    // while complete commands are found
    while( accessResult == COMPLETE_OPCMD_FOUND_MSG )
       {
        // add the new op command to the linked list
           // function: addNode
        localHeader = addNode( localHeader, newNodePtr );

        // get a new op command
           // function: getOpCommand
        accessResult = getOpCommand(  fileAccessPtr, newNodePtr );

        // update start end counts for later comparison
           // function: updateStartCount, updateEndCount
        startCount = updateStartCount( startCount, newNodePtr->opName );
        endCount = updateStartCount( endCount, newNodePtr->opName );
       }

       // after loop completion, check for last op command found
       if( accessResult == LAST_OPCMD_FOUND_MSG )
          {
           // check for start and end op code counts equal
           if( startCount == endCount )
              {
               // add the last node to the linked list
                  // function: addNode
               localHeader = addNode( localHeader, newNodePtr );

               // set access result to no error for later operation
               accessResult = NO_ERR;

               // check last line for incorrect end descriptor
               if( getLineTo( fileAccessPtr, MAX_STR_LEN, PERIOD,
                                 dataBuffer, IGNORE_LEADING_WS ) != NO_ERR
                 || compareString( dataBuffer, "End Program Meta-Data Code" )
                                                                    != STR_EQ )
                  {
                   // set access result to corrupted descriptor error
                   accessResult = MD_CORRUPT_DESCRIPTION_ERR;
                  }
              }
           
           // otherwise, assume start count not equal to end error
           else
              {
               // set access result to unbalance start/end error
               accessResult = NUBALANCED_START_END_ERR;
              }
          }

       // check for any errors found 
       if( accessResult != NO_ERR )
          {
           // clear the op command list
              // function: clearMetaDataList
           localHeader = clearMetaDataList( localHeader );
          }

       // close access file
          // function: fclose
       fclose( fileAccessPtr );

       // release temporary structure memory
          // function: free
       free( newNodePtr );

       // assign temporary local head pointer to parameter return pointer
       *opCodeDataHead = localHeader;

    //return access result
    return accessResult;
   }

/*
Function Name: getOpCommand
Algorithm: acquires one op command, vertifies all parts of it,
           return as parameter
Precondition: file is open and file cursor is at beginning 
              of an op code
Postcondition: in correct operation,
               find, tests, and returns op command as parameter.
               and returns status as integer
               - either complete op command found, 
               or last op command found
Expections: correctly and appropriately responds to and reports file
            access failure, incorrectly formatted op litter,
            incorrectly formatted op name, incorrectly or out of 
            command value
Notes: none
*/
int getOpCommand( FILE *filePtr, OpCodeType *inData )
   {
    // initialize function/varioubles

       // initialize local constants - max op name and op value length
       const int MAX_OP_NAME_LENGTH = 10;
       const int MAX_OP_VALUE_LENGTH = 9;

       // initialize integer buffer value to zero
       int intBuffer = 0;

       // initialize source and destination indices to zero
       int sourceIndex = 0, destIndex = 0;

       // initialize other variables
       int accessResult = 0;
       char strBuffer[ STD_STR_LEN ];

    // get whole op command as s string
       // function: getLineTo
    accessResult = getLineTo( filePtr, STD_STR_LEN, SEMICOLON,
                                          strBuffer, IGNORE_LEADING_WS );

    // check for successful access
    if( accessResult == NO_ERR )
       {
        // assign op command letter to struct component
        inData->opLtr = strBuffer[ sourceIndex ];
       }

    // otherwise, assume unsuccessful access
    else
       {
        // set pointer to data structure to null
        inData = NULL;

        // return op command to failure
        return OPCMD_ACCESS_ERR;
       }

    // vertify op command letter
    switch( inData->opLtr )
       {
        // check for all correct case
        case 'S':
        case 'A':
        case 'P':
        case 'M':
        case 'I':
        case 'O':
           break;

        // otherwise, assume not a correct case
         default:
            // set op command pionter to null
            inData = NULL;

            // return op command letter error
            return CORRUPT_OPCMD_LETTER_ERR;
       }

    // loop until left paren found
     while( sourceIndex < STD_STR_LEN && strBuffer[ sourceIndex ] != LEFT_PAREN )
        {
         // increment source index
         sourceIndex ++;
        }

    // skip left paren element, incremant source index
    sourceIndex ++;

    // set op command text
    // loop until right paren found
    while( sourceIndex < STD_STR_LEN
            && destIndex < MAX_OP_NAME_LENGTH
               && strBuffer[ sourceIndex ] != RIGHT_PAREN )
        {
         // acquire letter
         inData->opName[ destIndex ] = strBuffer[ sourceIndex ];
             
         // increment source index
         destIndex++, sourceIndex++;

         // set end//null character to current end of string
         inData->opName[ destIndex ] = NULL_CHAR;
        }

    // check for incorrect op string
       // function: checkOpString
    if( checkOpString( inData->opName ) == False )
       {
        // set struct to null
        inData = NULL;

        // return corrupt op command found
        return CORRUPT_OPCMD_NAME_ERR;
       }

    // skip right paren element - increment source index, reset dest idex
    sourceIndex++;
    destIndex = 0;

    // get integer value
    // loop while digits are found
       // function: isDigit
     while( sourceIndex < STD_STR_LEN
            && destIndex < MAX_OP_VALUE_LENGTH
               && inDigit( strBuffer[ sourceIndex ] ) == True )
        {
         // nultiply current buffer by ten
         intBuffer *= 10;

         // add next integer value, converted from character to integer
         intBuffer += (int)( strBuffer[ sourceIndex ] - '0' );

         // increment indices
         destIndex++, sourceIndex++;
        }

    // check for loop overrun failure, check specified lengths
    if( sourceIndex == STD_STR_LEN || destIndex == MAX_OP_VALUE_LENGTH )
       {
        // set struct to null
        inData = NULL;

        // return corrput op command value found
        return CORRUPT_OPCMD_VALUE_ERR;
       }

    // set value to data structure component
    inData->opValue = intBuffer;

    // check for last data structure component
       // function: compareString
    if( inData->opLtr == 'S'
        && compareString( inData->opName, "end" ) == STR_EQ )
       {
        // return last op command found message
        return LAST_OPCMD_FOUND_MSG ;
       }

    //return complete op command found message
    return COMPLETE_OPCMD_FOUND_MSG;
   }

/*
Function Name: updateStartCount
Algorithm: updates number of "start" op command found in file 
Precondition: count >= 0, op string has "start" or other op name
Postcondition: if op string has "start", input count + 1 is returned;
               otherwise, input count is returned unchanged
Expections: none
Notes: none
*/
int updateStartCount( int count, char *opString )
   {
    // check for "start" in op string
       // function: compareString
    if( compareString( opString, "start" ) == STR_EQ )
       {
        // return increment start count
        return count + 1;
       }

    // return unchaged start count
    return count;
   }

/*
Function Name: updateEndCount
Algorithm: updates number of "end" op command found in file 
Precondition: count >= 0, op string has "end" or other op name
Postcondition: if op string has "end", input count + 1 is returned;
               otherwise, input count is returned unchanged
Expections: none
Notes: none
*/
int updateEndCount( int count, char *opString )
   {
    // check for "end" in op string
       // function: compareString
    if( compareString( opString, "end" ) == STR_EQ )
       {
        // return increment start count
        return count + 1;
       }

    // return unchaged start count 
    return count;
   }

/*
Function Name: addNode
Algorithm: adds op command structure with data to a linked list
Precondition: linked list pointer assigned to null or to one command
              struct pointer assigned to op command structure
Postcondition: assigns new structure node to beginning of a linked list
               or and of access/availablilty
Expections: none
Notes: assume memory access/availability
*/
OpCodeType *addNode( OpCodeType *localPtr, OpCodeType *newNode )
   {
    //check for loacl pointer assigned to null
    if( localPtr == NULL )
       {
        // access memory for new Link/node
           // function: malloc
        localPtr = ( OpCodeType * ) malloc( sizeof( OpCodeType ) );

        // assign all three values to newly created node
        // assign next poiter to null
           // function: copyString
        localPtr->opLtr = newNode->opLtr;
        copyString( localPtr->opName, newNode->opName );
        localPtr->opValue = newNode->opValue;
        localPtr->next = NULL;

        // return current local pointer
        return localPtr;
       }

    // assume end of list not found yet
    // assign recursive function to current's next link
       // function: addNode
    localPtr->next = addNode( localPtr->next, newNode );

    //return current local pinter
    return localPtr;
   }

/*
Function Name: checkopString
Algorithm: checks tested op string against list of possible
Precondition: tested op string is correct C-Style string
              wirh potential op command name in it
Postcondition: in correct operation,
               vertifies the test string with one
               of the potential op strings and returns true;
               otherwise, return false
Expections: none
Notes: none
*/
Boolean checkOpString( char *testStr )
   {
    // check for all possible op names
       // function: compareString
    if( compareString( testStr, "access" )       == STR_EQ
     || compareString( testStr, "allocate" )     == STR_EQ
     || compareString( testStr, "end" )          == STR_EQ
     || compareString( testStr, "hard drive" )   == STR_EQ
     || compareString( testStr, "keyboard" )     == STR_EQ
     || compareString( testStr, "printer" )      == STR_EQ
     || compareString( testStr, "monitor" )      == STR_EQ
     || compareString( testStr, "run" )          == STR_EQ
     || compareString( testStr, "start" )        == STR_EQ )
       {
        // return found - true
        return True;
       }

    //return failure - false
    return False;
   }

/*
Function Name: isDigit
Algorithm: check for character digit, return result
Precondition: test value is character
Postcondition: if test vaule is a vaule '0' < value < '9',
               return true, otherwise retruns false
Expections: none
Notes: none
*/
Boolean inDigit( char testChar )
   {
    // check for test character between characters '0' - '9' inclusive
    if( testChar >= '0' && testChar <= '9' )
       {
        // return true
        return True;
       }

    // otherwise, assume character is not digit, return false
    return False;
   }


/*
Function Name: displayMetaDataError
Algorithm: uses enum/constant values as indices to select display string,
           then displays error message with selected string
Precondition: integer input code has one of the enumerated code values
Postcondition: error message is displayed with the correct
               load error item
Expections: none
Notes: none
*/
void displayMetaDataError( int code )
   {
    // create string error list, 10 items, max 35 letters
    // include 3 error to monitor with selected error string
    char errList[ 10 ][ 35 ] =
                   { "No Error",
                     "Incomplete File Error",
                     "Input Buffer Overrun",
                     "MD File Access Error",
                     "MD Corrupt Descriptor Error",
                     "Op Command Access Error",
                     "Corrupt Op Command Letter Error",
                     "Corrupt Op Command Name Error",
                     "Corrupt Op Command Value Error",
                     "Unbalanced Start-End Code Error" };
                     
    // display error to monitor with selected error string
       // function: printf
    printf( "\nFATAL ERROR: %s, Program aborted\n", errList[ code ] );
   }

/*
Function Name: clearMetaDataList
Algorithm: recursively iterates through op linked list ,
           returns memory to OS from the bottom of the list upward
Precondition: linked list, with or without data
Postcondition: all node memory, if any, is returned to OS,
               return pointer is set to null
Expections: none
Notes: none
*/
OpCodeType *clearMetaDataList( OpCodeType *localPtr )
   {
    // check for local poiter not set to null
    if( localPtr != NULL )
       {
        // check for local poiter's next node not null
        if( localPtr->next != NULL )
           {
            // call recursive call, function with next pointer
               // function: clearMetaDataList
            clearMetaDataList( localPtr->next );
           }

        // after recursive call, release memory to OS
           // function: free
        free( localPtr );
       }
    // return null to calling function
    return NULL;
   }




















