https://powcoder.com
代写代考加微信 powcoder
Assignment Project Exam Help
Add WeChat powcoder
//header files
#include "StringUtils.h"

// glabal constants
const int MAX_STR_LEN = 200;
const char NULL_CHAR = '\0';
const int STD_STR_LEN = 80;
const int SUBSTRING_NOT_FOUND = -101;
const int STR_EQ = 0;
const char SPACE = ' ';
const char COLON = ':';
const char PERIOD = '.';
const char SEMICOLON = ';';
const char LEFT_PAREN = '(';
const char RIGHT_PAREN = ')';

const Boolean IGNORE_LEADING_WS = True;
const Boolean ACCEPT_LEADING_WS = False;
/*
function name: getStirngLength
Algorihtm: find the length of the stirng, up to the null character
Precondition: give C-style with null character at the end
Postcondition: return the number of characters (int) from the beginning
               to the null character
Expections: none
Note: limit test loop to maxium characters for safety
*/
int getStringLength( char *testStr )
   {
    // iniitalize function/variales
    int index = 0;

    // loop up to null character or limit
    while( index < MAX_STR_LEN && testStr[ index ] != NULL_CHAR )
       {
        // increment
        index++;
       }
    // loop to end

    // return size
    return index;
   }

/*
function name: copyString
Algorihtm: copies contents of one string into another
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng; destiration string is passed in as 
              a parameter with enough memory to accept the source string
Postcondition: destination string contains an exact copy
               of the cource string
Expections: none
Note: limit test loop to maxium characters for safety
*/
void copyString( char *destinaton, char *source )
   {
    // initialized function/variables
    int index = 0;

    // loop until null character is found in source string
    // loop limited to MAX_STR_LEN
    while( index < MAX_STR_LEN && source[ index ] != NULL_CHAR )
       {
        // assign source character to destination element
        destinaton[ index ] = source [ index ];

        // increment index
        index++;

        // assign null character to next destination element
        destinaton[ index ] = NULL_CHAR;
       }
    // end loop
   }

/*
function name: concatenateString
Algorihtm: concatentes or appends contents of one string
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng; destiration string is passed in as 
              a parameter with enough memory to accept the source string
Postcondition: destination string contains its original string with 
               the source string appended or concatenated to the end of it
Expections: none
Note: limit test loop to maxium characters for safety
*/
void concatenateString( char *destination, char *source )
   {
    // initialized function/variables
   
       // set destination index to the length of destination string
       int destIndex = getStringLength( destination );

       // set source index to 0
       int sourceIndex = 0;

    // loop to end of source index (null character)
    // loop limited to MAX_STR_LEN
    while( sourceIndex < MAX_STR_LEN && source[ sourceIndex ] != NULL_CHAR )
       {
        // assign source character to destination at destination index
        destination[ destIndex ] = source [ sourceIndex ];

        // increment source and destination index 
        destIndex++;
        sourceIndex++;

        // assign null character to next destination element
        destination[ destIndex ] = NULL_CHAR; 
       }
    // end loop
   }

/*
function name: compareString
Algorihtm: compare two strings alphabetically such that:
           if oneStr < otherStr, the functon returns a value < 0
           if oneStr > otherStr, the functon returns a value > 0
           if oneStr == otherStr, the functon a 0
           if two strings are identical up to the point that one is longer,
           the difference in lengths will be returned
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng 
Postcondition: integer value returned ad specified
Expections: none
Note: limit test loop to maxium characters for safety
*/
int compareString( char *oneStr, char *otherStr )
   {
    // initialized function/variables
     
       // initialize index to zero
       int index = 0;

       // initialize other variables
       int difference;

    // loop to end of one of the two strings (null character)
    // loop limited to MAX_STR_LEN
    while( index < MAX_STR_LEN
             && oneStr[ index ] != NULL_CHAR
                && otherStr[ index ] != NULL_CHAR )
       {
        // find the differnece between the currently aligned characters
        difference = oneStr[ index ] - otherStr[ index ];

        // check for non-zero difference
        if( difference != 0 )
           {
            // return non-zero differnece
            return difference;
           }

        // increment index
        index++;
       }
    // end loop
     
    // assume strings are equal at this piont,return string length diffrnece
        // function: getStringLength 
    return getStringLength( oneStr ) - getStringLength( otherStr ); 
   }

/*
function name: getSubString
Algorihtm: captures sub Stirng within larger string
           between two inclusive indices
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng; and another string parameter 
              with enough memory to hold the resulting subString
Postcondition: subString is returned as parameters
Expections: empty string returned if any of the index parameters
            are out of range      
Note: copy of source string is made internally to protect from alising
*/
void getSubString( char *destStr, char *sourceStr, 
                                     int starIndex, int endIndex )
   {
    // initialized function/variables
   
       // set length of source string
          // function: getStringLength
       int sourceStrLen = getStringLength( sourceStr );

       // initialized destination index to 0;
       int destIndex = 0;

       // initialized source index to start index parameter
       int sourceIndex = starIndex;

       // create pointer to temp string
       char *tempSourceStr;

    // check for indices with limits
    if( starIndex >= 0 && starIndex <= endIndex && endIndex < sourceStrLen )
       {
        // create temporary string, copy source string to it
           // function: malloc, copyString
        tempSourceStr = (char *) malloc( sourceStrLen + 1 );
        copyString( tempSourceStr, sourceStr );

        // loop across requested substring (indices)
        while( sourceIndex <= endIndex )
           {
            // assign source character to destiantion element
            destStr[ destIndex ] = tempSourceStr[ sourceIndex ];
       
            // incremant indicies
            destIndex++;
            sourceIndex++;

            // add null character to next destination string element
            destStr[ destIndex ] = NULL_CHAR;
           }
        // end loop

        // release memory used for temp source string
           // function: free
        free( tempSourceStr );
       }

    // otherwise, assume indices not in limits
    else
       {
        // create empty string with null character
        destStr[ 0 ] = NULL_CHAR;
       }
   }

/*
function name: findSubStirng
Algorihtm: linear serch for given substring within a given test string
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng, and given search string with a null
              character ('\0') at the end of that string
Postcondition: index of subString location returned,
               or SUBSTRING_NOT_FOUND constant is returned
Expections: none
Note: none
*/
int findSubString( char *testStr, char *searchSubStr )
   {
    // initialized function/variables

       // initialize test string kength
          // function: getStringLength
       int testStrLen = getStringLength( testStr );

       // initialize master index - location of sub string start point
       int masterIndex = 0;

       // initialize  other variables
       int searchIndex, internalIndex;

    // loop across test string
    while( masterIndex < testStrLen )
       {
        // set internal loop index to current test index
        internalIndex = masterIndex;
 
        // set internal search index to zero
        searchIndex = 0;

        // loop to end of test string
        // while teststring/sub string chrarcters are the same
        while( internalIndex <= testStrLen
                  && testStr[ internalIndex ] == searchSubStr[ searchIndex ] )
           {
            // incremant test string, substring indicies
            internalIndex++;
            searchIndex++;

            // check for end of substring (search completed)
            if( searchSubStr[ searchIndex ] == NULL_CHAR )
               {    
                // return current test string index
                return masterIndex;
               }
           }
        // end loop

        // increment current test string inedx
        masterIndex++;
       }

    // assume tests have failed at this piont, return SUBSTRING_NOT_FOUND
    return SUBSTRING_NOT_FOUND;
   }

/*
function name: setStrToLowerCase
Algorihtm: interates through string, set all upper case letters
           to lower case without changing any other charcters
Precondition: give C-style soure string, having a null character ('\0')
              at end of stirng; destiration string is passed  with 
              enough memory to hold the lower case string
Postcondition: all upper case letters in given string are set to 
               lower case; no change to any othe characters
Expections: limit on stirng loop in case incorrect string format
Note: copy of source string is made internally to protect from aliaing
*/
void setStrToLowerCase( char *destStr, char *sourceStr )
   {
    // initialize function/variables

       // create temporary source string
          // function: getStringLength, malloc
       int strLen = getStringLength( sourceStr );
       char *tempStr = (char*) malloc( strLen + 1 );

       // initialize source string index to 0
       int index = 0;

    // copy source string to temporary string
       // function: copyString
    copyString( tempStr, sourceStr );

    // loop to end of temporary string
    // loop limited to MAX_STR_LEN
    while( index < MAX_STR_LEN && tempStr[ index ] != NULL_CHAR )
       {
        // change letter to lower case as needed ad assign
        // to destination string
            // function: setCharToLowerCase
        destStr[ index ] = setCharToLowerCase( tempStr[ index ] );

        // increment index
        index++;

        // add null character to next destination string element
        destStr[ index ] = NULL_CHAR;
       }
    // end loop 

    // release temp string memory
       // function: free
    free( tempStr );
   }

/*
function name: setCharToLowerCase
Algorihtm: test character parameter for upper case, change it to upper case, 
           makes no change if not upper case
Precondition: give character value
Postcondition: upper case letter is set to lower case,
               otherwise, character is returned unchanged
Expections: none
Note: none
*/
char setCharToLowerCase( char testChar )
   {
    // initialize function/variables
      
       // none

    // check for character between 'A'and 'Z' inclusive
    if( testChar >= 'A' && testChar <= 'Z' )
       {
        // convert upper case letter to lower case
        testChar = (char) ( testChar - 'A' + 'a' );
       }

    // return character
    return testChar;
   }

/*
function name: getLineTo
Algorihtm: find given text in file, skipping white space if specified,
           stops searching at given character or length
Precondition: file is open with vaild file pointer;
              char buffer has adequate memory for data;
Postcondition: ignores leading white space if specified;
               captures all printable characters and stores in string buffer
Expections: return INCOMPLETE_FILE_ERR if no valid data found;
            return NO_ERR if successful opeation
Note: none
*/
int getLineTo( FILE *filePtr, int bufferSize, char stopChar,
                          char *buffer, Boolean omitLeadWhiteSpace )
   {
    // initialize function/variables
       
       // initialize character index
       int charIndex = 0;

       // initialize status return to NO_ERR
       int statusReturn = NO_ERR;

       // initialize buffer size available flag to true
       Boolean bufferSizeAvailable = True;

       // initialze other variables
       int charAsInt;

    // get the first character
       // function: fgetc
    charAsInt = fgetc( filePtr );

    // use a loop to consume leading white space, if flagged
    while( omitLeadWhiteSpace == True
             && charAsInt != (int) stopChar
                  && charIndex < bufferSize
                       && charAsInt <= (int) SPACE )
       {
        // get next character (as integer)
           // function: fgetc
        charAsInt = fgetc( filePtr );
       }
    // end loop

    // capture string
    // loop while character is not stop character and buffer size is available
    while( charAsInt != (int) stopChar && bufferSizeAvailable == True )
       {
        // check for input failure
           // function: isEndofFile
        if( isEndOfFile( filePtr ) == True )
           {
            // return imcomplete file error
            return INCOMPLETE_FILE_ERR;
           }

        // check for usable (printable) character
        if( charAsInt >= (int) SPACE )
           {
            // assign input character to buffer string
            buffer[ charIndex ] = (char) charAsInt;

            // increment index
            charIndex++;
           }

        // set next buffer element to null character
        buffer[ charIndex ] = NULL_CHAR; 

        // check for not at end of buffer size
        if( charIndex < bufferSize - 1 )
           {
            // get a new character
               // function: fgetc
            charAsInt = fgetc( filePtr );
           }

        // otherwise, assume end to the size
        else
           {
            // set buffer size Boolen to false to end loop
            bufferSizeAvailable = False;

            // set status return to buffer overrun error
            statusReturn = INPUT_BUFFER_OVERRUN_ERR;
           }
       }
       // end loop

    // return status data 
    return statusReturn;
   }

/*
function name: isEndOfFile
Algorihtm: reports end of file, using feof
Precondition: file is open with vaild file pointer;
Postcondition: reports end of file
Expections: none
Note: none
*/
Boolean isEndOfFile( FILE *filePtr )
   {
    // intialize functions/variables

    // check for feof end of the file response
       // function: feof
    if( feof( filePtr ) != 0 )
       {
        // return true
        return True;
       }

    // assume test failed at this point, return false
    return False;
   }










