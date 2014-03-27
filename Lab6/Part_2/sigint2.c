/*
 *  File:    sigint2.c
 *  Course:  CENG411
 *  Author:  Peter Jones
 *  Date:    Wednesday 26 March, 2014
 *  Purpose: This program opens a series of files read from fileList.txt, and opens them
 *           given a SIGINT interrupt 
 *
 */

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
  char str[100], buff[1024], stream[80];
  char * line, *mode;
  int len;

  /* Open file containing file names and modes */
  file1 = fopen("fileList.txt", "r");

  /* Read fileList.txt and separate each line into 2 tokens (name of file and file mode) */
  while((fgets(stream, 80, file1)) != NULL)
  {
    line = strtok(stream, " ");
    mode = strtok(NULL, " ");
    file2 = fopen(line, mode);
  }
 
  /* Go to the directory where files are and display them */
  sprintf(str, "/proc/%i/fd", getpid());
  chdir(str);
  dirp = opendir("."); 
  while(dirent = readdir(dirp))
  {
    if(strcmp(dirent->d_name, ".") == 0 || strcmp(dirent->d_name, "..") == 0) continue;
    else 
    {
    readlink(dirent->d_name, buff, sizeof(buff));
    fprintf(stdout, "File: %s\nFile path: %s \n\n", dirent->d_name, buff);
    }
  }
 
}

/* Start of main program */
int main(int argc, char * argv[],char * envp[])
{
  /* Declare handler */
  void h(int);

  fprintf(stdout, "Current process id: %d\nParent process id: %d\n", getpid(), getppid());
 
  /* Declare when to invoke handler */
  signal(SIGHUP, h);
  raise(SIGHUP);

  /* Loop to issue an interrupt */
//  for(;;) sleep(1);
  
  return 0;
}
