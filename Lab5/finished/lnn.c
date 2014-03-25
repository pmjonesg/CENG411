#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <getopt.h>
#include <stdlib.h>
#include <sys/stat.h>

#define LINK_ERR(err) if(err != 0)  {perror("Error: "); return(errno); } 

int main(int argc, char **argv)
{
  struct FLAGS
  {
    bool soft;
    bool force;
  } flags = {false, false};
  struct stat sb;

  int flag;
  int err;

  while((flag = getopt(argc, argv, "sf")) != -1)
  {
    switch(flag)
    {
      case 's':
	        flags.soft = true;
                break;
      case 'f':
                flags.force = true;
                break;
      case ':':
                fprintf(stdout, "Missing arguments");
                break;
      case '?':
      default:
                perror("Invalid flag");
    }
  }

  if(flags.force)
  {
    int exists;
    if(exists = !lstat(argv[3], &sb)) 
      unlink(argv[3]);
    err = link(argv[optind], argv[optind + 1]);
    LINK_ERR(err);
    return 0;
  }

  if(flags.soft)
  {
    err = symlink(argv[optind], argv[optind + 1]);
    LINK_ERR(err);
  } else
  {
    err = link(argv[optind], argv[optind + 1]);
    LINK_ERR(err);
  }
  

  return 0;
}
