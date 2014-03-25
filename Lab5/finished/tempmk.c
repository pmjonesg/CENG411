#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>

int main(int argc, char **argv)
{
  char *temp;
  struct stat fileExists;
 
  if(argc < 2)
    temp = strcat(argv[0], "XXXXXX");
  else
    temp = strcat(argv[1], "XXXXXX");
     
  char * file = mktemp(temp);

  if(fopen(file, "w+") != NULL)
  {
    fprintf(stdout, "%s\n", file);
  }
  else 
  {
    perror("Error: ");
    return errno;
  }
  
  int result = stat(file, &fileExists);
  if(result == 0)
     fprintf(stdout, "File exists\n");
  else
     fprintf(stdout, "File does not exist\n");
 
  return 0;
}
