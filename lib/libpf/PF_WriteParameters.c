/***********************************************************************
 *
 * Write parameters
 *
 ***********************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "PF.h"

int PF_WriteParameters(PF_ParameterEntry * const ParameterEntries,
                       size_t const NParameterEntries) {

 size_t i;
 size_t iParameterEntry;
 for(iParameterEntry=0;iParameterEntry<NParameterEntries;iParameterEntry++) {
  PF_ParameterEntry *ParameterEntry=&(ParameterEntries[iParameterEntry]);
  if(ParameterEntry->IsBoolean==1) {
   if( *((int *)ParameterEntry->Pointer) == 1) {
    printf("%s\n",ParameterEntry->Parameter);
   }
  } else if(ParameterEntry->IsArray==1) {
   for(i=0; i < *(ParameterEntry->NArrayElements); i++ ) {
    switch(ParameterEntry->Type) {
     case INTEGER:
      printf("%s[%lu] %i\n",ParameterEntry->Parameter,i,
       (*((int **     )(ParameterEntry->Pointer)))[i] );
      break;
     case LONG_INTEGER:
      printf("%s[%lu] %li\n",ParameterEntry->Parameter,i,
       (*((long int **)(ParameterEntry->Pointer)))[i] );
      break;
     case UNSIGNED_INTEGER:
      printf("%s[%lu] %u\n",ParameterEntry->Parameter,i,
       (*((unsigned int **)(ParameterEntry->Pointer)))[i] );
      break;
     case UNSIGNED_LONG_INTEGER:
      printf("%s[%lu] %lu\n",ParameterEntry->Parameter,i,
       (*((unsigned long int **)(ParameterEntry->Pointer)))[i] );
      break;
     case FLOAT:
      printf("%s[%lu] %e\n",ParameterEntry->Parameter,i,
       (*((float **   )(ParameterEntry->Pointer)))[i] );
      break;
     case DOUBLE:
      printf("%s[%lu] %e\n",ParameterEntry->Parameter,i,
       (*((double **  )(ParameterEntry->Pointer)))[i] );
      break;
     case CHAR:
      printf("%s[%lu] %c\n",ParameterEntry->Parameter,i,
       (*((char **  )(ParameterEntry->Pointer)))[i] );
      break;
     case STRING:
      printf("%s[%lu] %s\n",ParameterEntry->Parameter,i,
       (((char **  )(ParameterEntry->Pointer)))[i] );
      break;
     default:
      printf("%s: %i: ERROR: Unknown type %i\n",
             __FILE__,__LINE__,ParameterEntry->Type);
      return EXIT_FAILURE;
    }
   }
  } else {
   /* Regular Parameters = value entry */
   switch(ParameterEntry->Type) {
    case INTEGER:
     printf("%s %i\n",ParameterEntry->Parameter,
      *((int *     )ParameterEntry->Pointer) );
     break;
    case LONG_INTEGER:
     printf("%s %li\n",ParameterEntry->Parameter,
      *((long int *)ParameterEntry->Pointer) );
     break;
    case UNSIGNED_INTEGER:
     printf("%s %u\n",ParameterEntry->Parameter,
      *((unsigned int *)ParameterEntry->Pointer) );
     break;
    case UNSIGNED_LONG_INTEGER:
     printf("%s %lu\n",ParameterEntry->Parameter,
      *((long int *)ParameterEntry->Pointer) );
     break;
    case FLOAT:
     printf("%s %e\n",ParameterEntry->Parameter,
      *((float *   )ParameterEntry->Pointer) );
     break;
    case DOUBLE:
     printf("%s %e\n",ParameterEntry->Parameter,
      *((double *  )ParameterEntry->Pointer) );
     break;
    case STRING:
     printf("%s %s\n",ParameterEntry->Parameter,
      (char *)(ParameterEntry->Pointer) );
     break;
    default:
     printf("%s: %i: ERROR: Unknown type %i\n",
            __FILE__,__LINE__,ParameterEntry->Type);
     return EXIT_FAILURE;
   }
   
  } /* End of if IsBooleen, elseif IsArray, else tree */
  
 } /* End of loop over all parameters */

 return(EXIT_SUCCESS);
}
