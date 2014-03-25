#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <dirent.h>

#define REP_ERR { perror("Error: "); return(errno); }

int main(int argc, char **argv)
{
  DIR * dirp;
  struct dirent *dirent;
  dirp = opendir(".");
  char * directory;
  if((directory = getcwd(NULL, 0)) != NULL)
  {
    fprintf(stdout, "%s\n", directory);
    if(directory == NULL) REP_ERR;
  }
    
  chdir("/home/students/jnsp0116/");
  if((directory = getcwd(NULL, 0)) != NULL)
  {
    fprintf(stdout, "%s\n", directory);
    if(directory == NULL) REP_ERR;
  }


  return 0;
}
