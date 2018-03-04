/***********************************************************************
 *
 * Read a Parameter File
 *
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PF.h"

int PF_ReadParameterFile(FILE * const File,
                         PF_ParameterEntry * const ParameterEntries,
                         size_t const NParameterEntries) {

 char StrippedLine[MAX_LINE_LENGTH];
 char FileParameter[MAX_LINE_LENGTH];
 char Format[MAX_FORMAT_LENGTH];
 
 /* Rewind the file to the start */
 rewind(File);

 /* Read until out of lines */
 while( PF_RPF_ExtractCommentlessLine(File, StrippedLine) != NULL ) {

  if(strlen(StrippedLine) > 0 ) {
   
   /* Grab the first string in the line.
    *  Require: - only 1 parameter per line
    *           - parameter is the first string on a line. */
   int NParametersFound = sscanf(StrippedLine,"%s",FileParameter);

   size_t NMatch=0;
   size_t iParameterEntry;
   PF_ParameterEntry *ParameterEntry;
   switch(NParametersFound) {

    case 0:
     /* empty line */
     break;

    case 1:
     /* Scan through all parameters to see if the line pertains to it */
     for(iParameterEntry=0;iParameterEntry<NParameterEntries;iParameterEntry++) {
      if( strncmp(FileParameter, ParameterEntries[iParameterEntry].Parameter, MAX_LINE_LENGTH) == 0 ) {
       ParameterEntry=&(ParameterEntries[iParameterEntry]);
       NMatch++;

       /* If the parameter is simply a Boolean, set by the parameter name's presence
        * then set the value to 1. */
       if(ParameterEntry->IsBoolean==1) {
        *((int *)ParameterEntry->Pointer)=1;
       } else {
        /* Scan for a value or values */

        /* Find the position after the Parameter String */
        char *EndOfParameterNamePoint = strstr(StrippedLine,ParameterEntry->Parameter);
        EndOfParameterNamePoint += strlen(ParameterEntry->Parameter);

        if(ParameterEntry->IsArray==1) {
         /* Requirement: Parameter take a single argument: the number of elements in
          * the array */
         sscanf(EndOfParameterNamePoint,"%lu",ParameterEntry->NArrayElements);
         /* Read an array of numbers */
         int NArrayElements=PF_RPF_ReadArray(File,ParameterEntry);
         if(NArrayElements<0) {
          printf("%s: %i: ERROR: PF_RPF_ReadArray failed to read array\n",
                  __FILE__,__LINE__);
          return EXIT_FAILURE;
         }
        } else {
         /* Read the value */
         int ierr=PF_Format(ParameterEntry,Format);
         if(ierr != EXIT_SUCCESS) {
          printf("%s: %i: ERROR: Unable to determine a Format string for Type %i\n",
                 __FILE__,__LINE__,ParameterEntry->Type);
          return EXIT_FAILURE;
         }
         sscanf(EndOfParameterNamePoint, Format, ParameterEntry->Pointer);
        }
       }
      } /* End of if there was a match */
     } /* End of loop through all expected parameters */

     /* Warn if unexpected matching results */
     if(NMatch==0) {
      printf("%s: %i: WARNING: No match for parameter %s\n",
            __FILE__,__LINE__, FileParameter);
     }
     if(NMatch>1) {
      printf("%s: %i: WARNING: More than one match for parameter %s\n",
            __FILE__,__LINE__, FileParameter);
     }
     break;

    default:
     /* No Parameters in the line */
     break;

   } /* End switch(NParametersFound) */
  } /* End of if Not A Comment Line */
 } /* End loop over lines in file */

 return(EXIT_SUCCESS);
}
