#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>

void h(int signum)
{
  FILE *file1, *file2, *file3;
  DIR * dirp;
  struct dirent *dirent;
  char str[100];
  char buff[1024];
  char stream[80];
  char * line;
  int len, slen;
  char * mode;
  char * space;

  file1 = fopen("fileList.txt", "r");


  while((fgets(stream, 80, file1)) != NULL)
  {
    line = strtok(stream, " ");
    mode = strtok(NULL, " ");
    file2 = fopen(line, mode);
  }
  sprintf(str, "/proc/%i/fd", getpid());
  chdir(str);
  dirp = opendir("."); 
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
  DIR * dirp;
  struct dirent *dirent;
  char str[100];

 
  fprintf(stdout, "Current process id: %d\nParent process id: %d\n", getpid(), getppid());
 
  signal(SIGHUP, h);

  for(i=0;i<10;i++) { 
    fprintf(stdout, "Interrupt: %d\n", i);
    sleep(6);
  }
  
  fclose(file1);  
  fclose(file2);  
  fclose(file3); 
 
  return 0;
}
