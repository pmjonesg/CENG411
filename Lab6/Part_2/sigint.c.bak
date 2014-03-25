#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

void h(int signum)
{
  char *file1, *file2, *file3;
  DIR * dirp;
  struct dirent *dirent;
  char str[100];
  sprintf(str, "/proc/%i/fd", getpid());
  chdir(str);
  dirp = opendir("."); 
  char buff[1024];
  while(dirent = readdir(dirp))
  {
    readlink(dirent->d_name, buff, sizeof(buff));
    fprintf(stdout, "%s\n", buff);
  }
}

int main(int argc, char * argv[],char * envp[])
{
  void h(int);
  int i;
  FILE *file1, *file2, *file3;

  file1 = fopen("file1.txt", "w");
  file2 = fopen("file2.txt", "w");
  file3 = fopen("file3.txt", "w"); 

  fprintf(stdout, "Current process id: %d\nParent process id: %d\n", getpid(), getppid());
 
  signal(SIGINT, h);

  for(i=0;i<10;i++) { 
    fprintf(stdout, "Interrupt: %d\n", i);
    sleep(6);
  }
  
  fclose(file1);  
  fclose(file2);  
  fclose(file3); 
 
  return 0;
}
