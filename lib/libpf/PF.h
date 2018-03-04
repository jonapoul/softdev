#ifndef _PF_H_
#define _PF_H_

#include <stdlib.h>

#define MAX_PARAMETER_NAME_LENGTH 128

typedef enum DATATYPE {
 INTEGER,
 LONG_INTEGER,
 UNSIGNED_INTEGER,
 UNSIGNED_LONG_INTEGER,
 FLOAT,
 DOUBLE,
 CHAR,
 STRING
} DataType;

struct PF_ParameterEntry_struct {
 char Parameter[MAX_PARAMETER_NAME_LENGTH+1];
 void *Pointer;
 enum DATATYPE Type;
 int IsBoolean;
 int IsArray;
 size_t *NArrayElements; /* If an array, a pointer to an integer to store the array size */
};
typedef struct PF_ParameterEntry_struct PF_ParameterEntry;

#define COMMENT_CHARACTER "#"
#define MAX_LINE_LENGTH   512
#define MAX_FORMAT_LENGTH 4

int    PF_Format(PF_ParameterEntry const * const ParameterEntry,
                 char * const Format);
int    PF_ReadParameterFile(FILE * const File,
                            PF_ParameterEntry * const ParameterEntries,
                            size_t const NParameterEntries);
char * PF_RPF_ExtractCommentlessLine(FILE * const File,
                                     char * const StrippedLine);
int    PF_RPF_ReadArray(FILE * const File,
                        PF_ParameterEntry * const ParameterEntry);
int    PF_WriteParameters(PF_ParameterEntry * const ParameterEntries,
                          size_t const NParameterEntries);


#endif
