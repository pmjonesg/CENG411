#include <stdio.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char **argv, char * envp[])
{
  int file = rename(argv[1], argv[2]);
  if(file != 0)
  { 
  perror("Error: ");
  return(ENOENT);
  } 

  return 0;
}
