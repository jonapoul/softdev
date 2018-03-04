#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PF.h"


int PF_RPF_ReadArray(FILE * const File,
                     PF_ParameterEntry * const ParameterEntry) {
 int ierr;
 char *ValueString;
 char StrippedLine[MAX_LINE_LENGTH];
 char Format[MAX_FORMAT_LENGTH];
 /* Pointer types for storage */
 int               *IntegerPointer         = NULL;
 long int          *LongIntPointer         = NULL;
 unsigned int      *UnsignedIntPointer     = NULL;
 unsigned long int *UnsignedLongIntPointer = NULL;
 float             *FloatPointer           = NULL;
 double            *DoublePointer          = NULL;

 /* malloc, which depends on the data type */
 switch(ParameterEntry->Type) {

  case INTEGER:
   IntegerPointer =(int *)     malloc(sizeof(int)     * *(ParameterEntry->NArrayElements));
   break;

  case LONG_INTEGER:
   LongIntPointer =(long int *)malloc(sizeof(long int)* *(ParameterEntry->NArrayElements));
   break;

  case UNSIGNED_INTEGER:
   UnsignedIntPointer =(unsigned int *)malloc(sizeof(unsigned int)* *(ParameterEntry->NArrayElements));
   break;

  case UNSIGNED_LONG_INTEGER:
   UnsignedLongIntPointer =(unsigned long int *)malloc(sizeof(unsigned long int)* *(ParameterEntry->NArrayElements));
   break;

  case FLOAT:
   FloatPointer   =(float *)   malloc(sizeof(float)   * *(ParameterEntry->NArrayElements));
   break;

  case DOUBLE:
   DoublePointer  =(double *)  malloc(sizeof(double)  * *(ParameterEntry->NArrayElements));
   break;

  default:
   printf("%s: %i: ERROR: Unknown ParameterType %i\n",
          __FILE__,__LINE__,ParameterEntry->Type);
   return -1;
 }
 
 /* Get the Format string */
 ierr=PF_Format(ParameterEntry,Format);
 if(ierr != EXIT_SUCCESS) {
  printf("%s: %i: ERROR: Unable to determine a Format string for Type %i\n",
         __FILE__,__LINE__,ParameterEntry->Type);
  return EXIT_FAILURE;
 }

 /* Read in the values */
 size_t iArrayIndex;
 for(iArrayIndex=0;
     iArrayIndex < *(ParameterEntry->NArrayElements);
     iArrayIndex++) {
  /* Skip commented and blank lines */
  do {
   ValueString=PF_RPF_ExtractCommentlessLine(File, StrippedLine);
   if(ValueString==NULL) {
    printf("%s: %i: ERROR: Unable to read element\n",
           __FILE__,__LINE__);
    return -1;
   }
  } while(strlen(StrippedLine)==0);
  /* Scan the line for a number */
  switch(ParameterEntry->Type) {

   case INTEGER:
    sscanf(StrippedLine, Format, IntegerPointer + iArrayIndex );
    break;

   case LONG_INTEGER:
    sscanf(StrippedLine, Format, LongIntPointer + iArrayIndex );
    break;

   case UNSIGNED_INTEGER:
    sscanf(StrippedLine, Format, UnsignedIntPointer + iArrayIndex );
    break;

   case UNSIGNED_LONG_INTEGER:
    sscanf(StrippedLine, Format, UnsignedLongIntPointer + iArrayIndex );
    break;

   case FLOAT:
    sscanf(StrippedLine, Format, FloatPointer   + iArrayIndex );
    break;

   case DOUBLE:
    sscanf(StrippedLine, Format, DoublePointer  + iArrayIndex );
    break;

   default:
    printf("%s: %i: ERROR: Unknown ParameterType %i\n",
           __FILE__,__LINE__,ParameterEntry->Type);
    return -1;
  }
 }

 /* Now store the address of the Pointer into the location pointed to by
    ParameterEntry->Pointer */
 switch(ParameterEntry->Type) {

  case INTEGER:
   *((int **)ParameterEntry->Pointer)      = IntegerPointer;
   break;

  case LONG_INTEGER:
   *((long int **)ParameterEntry->Pointer) = LongIntPointer;
   break;

  case UNSIGNED_INTEGER:
   *((unsigned int **)ParameterEntry->Pointer) = UnsignedIntPointer;
   break;

  case UNSIGNED_LONG_INTEGER:
   *((unsigned long int **)ParameterEntry->Pointer) = UnsignedLongIntPointer;
   break;

  case FLOAT:
   *((float **)ParameterEntry->Pointer)    = FloatPointer;
   break;

  case DOUBLE:
   *((double **)ParameterEntry->Pointer)   = DoublePointer;
   break;

  default:
   printf("%s: %i: ERROR: Unknown ParameterType %i\n",
          __FILE__,__LINE__,ParameterEntry->Type);
   return -1;
 }

 return *(ParameterEntry->NArrayElements);
}
