#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void mysh_parse_command(const char* command,
                        int *argc, char*** argv) {
   int position = 0;
   int len;
   char *buffer = (char *)malloc(sizeof(char) * 8192);
   *argv = (char **)malloc(sizeof(char *) * 8192);
   for(*argc = 0 ;; (*argc)++) {
      while(*(command + position) == ' ' || *(command + position) == '\n' ||
                       *(command + position) == '\t') 
         position++;
      if(*(command + position) == '\0') break;
      sscanf(command + position, "%s", buffer);
      len = strlen(buffer);
      
      (*argv)[*argc] = (char *)malloc(sizeof(char) * (len + 1));
      strcpy((*argv)[*argc], buffer);

      position += len;
   }
   free(buffer);
   if(*argc > 0) *argv = (char **)realloc(*argv, *argc * sizeof(char *));
   else {
      (*argc)++;
      *argv = (char **)realloc(*argv, *argc * sizeof(char *));
      (*argv)[0] = (char *)malloc(sizeof(char));
      (*argv)[0][0] = '\0';
   }
}
