#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#define REP_ERROR { perror("Error: "); return(errno); }

int main(int argc, char **argv)
{
  int i = 1;
  for(i; i < argc; i++)
  {
    rmdir(argv[i]);
    REP_ERROR;
  }

  return 0;
}
