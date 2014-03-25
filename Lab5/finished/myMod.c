#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char **argv)
{ 
  int i = 0;
  int octal;
  sscanf(argv[1], "%o", &octal);
  for(i = 2; i < argc; i++)
  {
    int err = chmod(argv[i], octal);
    if(err != 0)
    {
      perror("Error: ");
      return(ENOENT);
    }
  }

  return 0;
}
