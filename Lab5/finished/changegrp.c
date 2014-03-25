#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <grp.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <dirent.h>

#define REP_ERROR { perror("Error: "); return(errno); }

int main(int argc, char **argv)
{
  int i;
  struct group *groupRec;

  if(NULL == (groupRec = getgrnam((char *) argv[1]))) {REP_ERROR;}
  else
  {
  for(i = 2; i < argc; i++)
  {
    int result = chown(argv[i], (uid_t)-1, groupRec->gr_gid);
    if(result == 0) REP_ERROR;
  } 
  }
  return 0;
}
