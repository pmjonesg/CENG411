#include <stdio.h>
#include <errno.h>

int main(int argc, char **argv)
{
  int err = unlink(argv[1]);
  if(err != 0)
  {
    perror("Error: ");
    return(EACCES);
  }
  return 0;
}
