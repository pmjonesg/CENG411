/*
 *  File:    sigint.c
 *  Course:  CENG411
 *  Author:  Peter Jones
 *  Date:    Wednesday 26 March, 2014
 *  Purpose: This program opens 3 files and displays the /proc/pid/fd showing that they're open
 *
 */


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdint.h>

/* This handler issues the command and reads the files open in /proc/pid/fd */
void h(int signum)
{
  char *file1, *file2, *file3;
  DIR * dirp;
  struct dirent *dirent;
  char str[100];

  /* Read path to str */
  sprintf(str, "/proc/%i/fd", getpid());

  /* Change directory and read the links for the files open */
  chdir(str);
  dirp = opendir("."); 
  char buff[1024];
  while(dirent = readdir(dirp))
  {
    readlink(dirent->d_name, buff, sizeof(buff));
    fprintf(stdout, "%s\n", buff);
  }
}

/* Start of main program */
int main(int argc, char * argv[],char * envp[])
{
  /* Declare handler */
  void h(int);
  int i;
  FILE *file1, *file2, *file3;

  /* Open files */
  file1 = fopen("file1.txt", "w");
  file2 = fopen("file2.txt", "w");
  file3 = fopen("file3.txt", "w"); 

  fprintf(stdout, "Current process id: %d\nParent process id: %d\n", getpid(), getppid());
 
  /* Call handler and give a SIGINT interrupt to display the path of files that have been opened */
  signal(SIGINT, h);
  raise(SIGINT, h);

  /* Loop to take the interrupt */
  for(;;) sleep(1);

  /* Close opened files */
  fclose(file1);  
  fclose(file2);  
  fclose(file3); 
 
  return 0;
}
