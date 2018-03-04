#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PF.h"

int PF_Format(PF_ParameterEntry const * const ParameterEntry, char *Format) {

 switch(ParameterEntry->Type) {
  case INTEGER:
   strncpy(Format,"%i" ,MAX_FORMAT_LENGTH);
   break;
  case LONG_INTEGER:
   strncpy(Format,"%li",MAX_FORMAT_LENGTH);
   break;
  case UNSIGNED_INTEGER:
   strncpy(Format,"%u" ,MAX_FORMAT_LENGTH);
   break;
  case UNSIGNED_LONG_INTEGER:
   strncpy(Format,"%lu",MAX_FORMAT_LENGTH);
   break;
  case FLOAT:
   strncpy(Format,"%f" ,MAX_FORMAT_LENGTH);
   break;
  case DOUBLE:
   strncpy(Format,"%lf",MAX_FORMAT_LENGTH);
   break;
  case CHAR:
   strncpy(Format,"%c" ,MAX_FORMAT_LENGTH);
   break;
  case STRING:
   strncpy(Format,"%s" ,MAX_FORMAT_LENGTH);
   break;
  default:
   printf("%s: %i: ERROR: Unknown Type %i\n",
          __FILE__,__LINE__,ParameterEntry->Type);
   return EXIT_FAILURE;
 }

 return EXIT_SUCCESS;
}
