#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "PF.h"


char * PF_RPF_ExtractCommentlessLine(FILE * const File, char * const StrippedLine) {
 /* Read a line from the file.
  * Return the line from the beginning up to immediately before the first
  *  comment character.
  * Return NULL if the End of File
  */

 char Line[MAX_LINE_LENGTH];

 char *ErrorStr=fgets(Line, MAX_LINE_LENGTH, File);

 if( ErrorStr == NULL ) {
  /* EOF */
  return NULL;
 }

 for (size_t i = 0; i < strlen(Line); i++) {
   if (Line[i] == '\n') Line[i] = '\0';
 }

 /* Ignore everything after the first comment character */
 char *CommentPoint=strstr(Line,COMMENT_CHARACTER);
 if(CommentPoint!=NULL) {
  /* Comment somewhere in the line. Set it's position to the EOL */
  strncpy(CommentPoint,"\0",1);
 }

 /* Copy the entire line, or from the line beginning to the comment character */
 strncpy(StrippedLine,Line,MAX_LINE_LENGTH);

 return StrippedLine; 
} 
