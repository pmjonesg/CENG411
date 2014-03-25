#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>

#define REP_ERROR { perror("Error: "); return(errno); }

int main(int argc, char **argv)
{
  umask(0);
  mode_t dirmask = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
  int i = 0;
  for(i; i < argc; i++)
  {
    int err = mkdir(argv[i], dirmask) == 0;
    if(err == -1)
      REP_ERROR;
    chmod(argv[i], 0711);
  }

  return 0;
}
